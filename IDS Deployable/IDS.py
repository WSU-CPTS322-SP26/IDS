from scapy.all import sniff, IP, TCP
from collections import defaultdict
import threading
import queue

class PacketCapture:
    def __init__(self):
        self.packet_queue = queue.Queue()
        self.stop_capture = threading.Event()

    def packet_callback(self, packet):
        original = packet

        # Walk down the payload chain until we find IP
        while packet and not packet.haslayer(IP):
            packet = packet.payload

        if packet and packet.haslayer(IP) and packet.haslayer(TCP):
            print("PACKET:", packet.summary())
            self.packet_queue.put(packet)
        else:
            # Debug print so we know what we're seeing
            print("NON-IP PACKET:", original.summary())

    def start_capture(self, interface):
        def capture_thread():
            sniff(iface=interface,
                  prn=self.packet_callback,
                  store=0,
                  stop_filter=lambda _: self.stop_capture.is_set())

        self.capture_thread = threading.Thread(target=capture_thread)
        self.capture_thread.start()

    def stop(self):
        self.stop_capture.set()
        self.capture_thread.join()


class TrafficAnalyzer:
    def __init__(self):
        self.port_hits = defaultdict(set)
        self.connections = defaultdict(list)
        self.flow_stats = defaultdict(lambda: {
            'packet_count': 0,
            'byte_count': 0,
            'start_time': None,
            'last_time': None
        })

    def analyze_packet(self, packet):
        if IP in packet and TCP in packet:
            ip_src = packet[IP].src
            ip_dst = packet[IP].dst
            port_src = packet[TCP].sport
            port_dst = packet[TCP].dport

            self.port_hits[ip_src].add(port_dst)

            flow_key = (ip_src, ip_dst, port_src, port_dst)

            # Update flow statistics
            stats = self.flow_stats[flow_key]
            stats['packet_count'] += 1
            stats['byte_count'] += len(packet)
            current_time = packet.time

            if not stats['start_time']:
                stats['start_time'] = current_time
            stats['last_time'] = current_time

            return self.extract_features(packet, stats)

    def extract_features(self, packet, stats):
        duration = stats['last_time'] - stats['start_time']
        if duration == 0:
            duration = 1e-6  # tiny non-zero value to avoid division by zero

        return {
            'packet_size': len(packet),
            'flow_duration': duration,
            'packet_rate': stats['packet_count'] / duration,
            'byte_rate': stats['byte_count'] / duration,
            'tcp_flags': packet[TCP].flags,
            'window_size': packet[TCP].window,
            'packet_count': stats['packet_count'],
            'source_ip': packet[IP].src
        }

    def analyze_json_dict(self, msg: dict) -> dict | None:
        """
        Accept a parsed JSON packet dict from the TCP socket listener and
        return a features dict in the same shape as extract_features().
        Returns None if the dict is missing required fields.
        """
        required = ('source_ip', 'destination_ip', 'source_port',
                    'destination_port', 'length', 'tcp_flags')
        if not all(k in msg for k in required):
            print(f"[SocketListener] Dropping malformed message: {msg}")
            return None

        ip_src   = msg['source_ip']
        ip_dst   = msg['destination_ip']
        port_src = int(msg['source_port'])
        port_dst = int(msg['destination_port'])
        pkt_size = int(msg['length'])
        tcp_flags = int(msg['tcp_flags'])

        # Track unique destination ports per source IP (same as analyze_packet)
        self.port_hits[ip_src].add(port_dst)

        flow_key = (ip_src, ip_dst, port_src, port_dst)
        stats = self.flow_stats[flow_key]
        stats['packet_count'] += 1
        stats['byte_count']   += pkt_size

        # Use wall-clock time when no packet timestamp is available
        import time
        current_time = time.time()
        if not stats['start_time']:
            stats['start_time'] = current_time
        stats['last_time'] = current_time

        duration = stats['last_time'] - stats['start_time']
        if duration == 0:
            duration = 1e-6

        return {
            'packet_size':   pkt_size,
            'flow_duration': duration,
            'packet_rate':   stats['packet_count'] / duration,
            'byte_rate':     stats['byte_count']   / duration,
            'tcp_flags':     tcp_flags,
            'window_size':   msg.get('window_size', 0),
            'packet_count':  stats['packet_count'],
            'source_ip':     ip_src,
        }

import socket as _socket
import json as _json

class QtBridge:
    """
    Listens on 127.0.0.1:9999. Qt connects once and the connection is
    bidirectional:
      - Incoming data (Qt → IDS): parsed as JSON, placed on json_queue
      - Outgoing data (IDS → Qt): call push(alert) to send an alert back
    """

    HOST = "127.0.0.1"
    PORT = 9999

    def __init__(self, json_queue: queue.Queue):
        self.json_queue    = json_queue
        self.alert_queue   = queue.Queue()
        self._stop_event   = threading.Event()
        self._conn         = None          # active client socket
        self._conn_lock    = threading.Lock()
        self._thread       = None

    def start(self):
        self._thread = threading.Thread(target=self._listen_loop, daemon=True,
                                        name="QtBridge")
        self._thread.start()
        print(f"[QtBridge] Listening on {self.HOST}:{self.PORT}")

    def stop(self):
        self._stop_event.set()
        self.alert_queue.put(None)         # unblock sender thread
        try:
            with _socket.create_connection((self.HOST, self.PORT), timeout=1):
                pass
        except Exception:
            pass
        if self._thread:
            self._thread.join(timeout=3)

    def push(self, alert: dict):
        """Called by AlertSystem.generate_alert() to send an alert to Qt."""
        self.alert_queue.put(alert)

    # ------------------------------------------------------------------
    def _listen_loop(self):
        srv = _socket.socket(_socket.AF_INET, _socket.SOCK_STREAM)
        srv.setsockopt(_socket.SOL_SOCKET, _socket.SO_REUSEADDR, 1)
        srv.bind((self.HOST, self.PORT))
        srv.listen(1)
        srv.settimeout(1.0)

        while not self._stop_event.is_set():
            try:
                conn, addr = srv.accept()
            except _socket.timeout:
                continue
            except OSError:
                break

            print(f"[QtBridge] Qt connected from {addr}")
            with self._conn_lock:
                self._conn = conn

            # Start sender thread for this connection
            send_thread = threading.Thread(target=self._send_loop,
                                           args=(conn,), daemon=True,
                                           name="QtBridgeSender")
            send_thread.start()

            try:
                self._recv_loop(conn)
            finally:
                with self._conn_lock:
                    self._conn = None
                conn.close()
                print(f"[QtBridge] Qt disconnected")

        srv.close()

    def _recv_loop(self, conn: _socket.socket):
        """Read incoming packet JSON from Qt."""
        buf = ""
        conn.settimeout(1.0)

        while not self._stop_event.is_set():
            try:
                chunk = conn.recv(4096).decode("utf-8", errors="replace")
            except _socket.timeout:
                continue
            except (ConnectionResetError, OSError):
                break

            if not chunk:
                break

            buf += chunk
            while "\n" in buf:
                line, buf = buf.split("\n", 1)
                line = line.strip()
                if not line:
                    continue
                try:
                    msg = _json.loads(line)
                    self.json_queue.put(msg)
                except _json.JSONDecodeError as e:
                    print(f"[QtBridge] JSON parse error: {e} | raw: {line!r}")

    def _send_loop(self, conn: _socket.socket):
        """Send outgoing alert JSON to Qt."""
        while not self._stop_event.is_set():
            alert = self.alert_queue.get()
            if alert is None:
                break
            try:
                conn.sendall((_json.dumps(alert) + "\n").encode("utf-8"))
            except OSError:
                # Connection dropped — put alert back and exit
                self.alert_queue.put(alert)
                break


from sklearn.ensemble import IsolationForest
import numpy as np

class DetectionEngine:
    def __init__(self, traffic_analyzer):
        self.traffic_analyzer = traffic_analyzer
        self.anomaly_detector = IsolationForest(
            contamination=0.1,
            random_state=42
        )
        self.signature_rules = self.load_signature_rules()
        self.training_data = []

    def load_signature_rules(self):
        return {
            'syn_flood': {
                'condition': lambda features: (
                    features['tcp_flags'] == 2 and
                    features['packet_rate'] > 50 and
                    features['flow_duration'] > 0.005 and
                    features['packet_count'] > 3
                )
            },
            'port_scan': {
                'condition': lambda features: (
                    len(self.traffic_analyzer.port_hits[features['source_ip']]) >= 5 and
                    features['packet_rate'] > 100 and
                    features['flow_duration'] > 0.01
                )
            }
        }

    def train_anomaly_detector(self, normal_traffic_data):
        self.anomaly_detector.fit(normal_traffic_data)

    def detect_threats(self, features):
        threats = []

        # Signature-based detection
        for rule_name, rule in self.signature_rules.items():
            if rule['condition'](features):
                threats.append({
                    'type': 'signature',
                    'rule': rule_name,
                    'confidence': 1.0
                })

        # Anomaly-based detection
        feature_vector = np.array([[
            features['packet_size'],
            features['packet_rate'],
            features['byte_rate']
        ]])

        anomaly_score = self.anomaly_detector.score_samples(feature_vector)[0]
        if anomaly_score < -0.5:
            threats.append({
                'type': 'anomaly',
                'score': anomaly_score,
                'confidence': min(1.0, abs(anomaly_score))
            })

        return threats


import logging
import json
from datetime import datetime, timezone
import requests

class AlertSystem:
    def __init__(self, log_file="ids_alerts.log", es_url=None, es_queue=None, alert_pusher=None):
        self.es_url       = es_url
        self.es_queue     = es_queue
        self.alert_pusher = alert_pusher   # AlertPusher instance (may be None)
        self.logger       = logging.getLogger("IDS_Alerts")
        self.logger.setLevel(logging.INFO)

        handler   = logging.FileHandler(log_file)
        formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
        handler.setFormatter(formatter)
        self.logger.addHandler(handler)

    def send_to_elasticsearch(self, alert):
        if not self.es_url:
            return
        self.es_queue.put(("ids-alerts", alert))

    def generate_alert(self, threat, packet_info):
        alert = {
            'timestamp':       datetime.now(timezone.utc).isoformat(),
            'threat_type':     threat['type'],
            'source_ip':       packet_info.get('source_ip'),
            'destination_ip':  packet_info.get('destination_ip'),
            'confidence':      threat.get('confidence', 0.0),
            'details':         threat
        }

        self.logger.warning(json.dumps(alert))
        self.send_to_elasticsearch(alert)

        # Push to Qt alert window if connected
        if self.alert_pusher:
            self.alert_pusher.push(alert)

        if threat['confidence'] > 0.8:
            self.logger.critical(
                f"High confidence threat detected: {json.dumps(alert)}"
            )


import os
import socket
from scapy.all import get_if_list, get_if_addr


class IntrusionDetectionSystem:
    def __init__(self, interface=None):
        if interface is None:
            interface = self.auto_select_interface()

        self.packet_capture  = PacketCapture()
        self.traffic_analyzer = TrafficAnalyzer()
        self.detection_engine = DetectionEngine(self.traffic_analyzer)

        es_url = os.getenv("ES_URL", "http://localhost:9200")
        self.es_queue     = queue.Queue()
        self.alert_system = AlertSystem(es_url=es_url, es_queue=self.es_queue,
                                        alert_pusher=None)  # set after qt_bridge is created

        self.detection_engine.train_anomaly_detector([[50, 1, 100]])
        self.interface = interface

        # Bidirectional bridge to Qt on port 9999
        self.json_queue = queue.Queue()
        self.qt_bridge  = QtBridge(self.json_queue)
        self.alert_system.alert_pusher = self.qt_bridge  # alerts go back over same socket

    def auto_select_interface(self):
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        try:
            s.connect(("8.8.8.8", 80))
            local_ip = s.getsockname()[0]
        finally:
            s.close()

        for iface in get_if_list():
            try:
                iface_ip = get_if_addr(iface)
                if iface_ip == local_ip:
                    return iface
            except:
                continue

        skip_keywords = [
            "Loopback", "Npcap", "Virtual", "VMware", "vEthernet",
            "Wi-Fi Direct", "Local Area Connection", "Bluetooth"
        ]
        for iface in get_if_list():
            if not any(k in iface for k in skip_keywords):
                try:
                    iface_ip = get_if_addr(iface)
                    if iface_ip and iface_ip != "0.0.0.0" and not iface_ip.startswith("127."):
                        return iface
                except:
                    continue

        raise RuntimeError("No valid network interface found")

    def _es_worker(self):
        while True:
            index_name, doc = self.es_queue.get()
            if index_name is None:
                break
            try:
                requests.post(
                    f"{self.alert_system.es_url}/{index_name}/_doc",
                    json=doc,
                    timeout=2
                )
            except Exception as e:
                print(f"ES worker POST error [{index_name}]: {e}")
            finally:
                self.es_queue.task_done()

    def _process_json_msg(self, msg: dict):
        """
        Extract features from a JSON packet dict and run the detection engine,
        mirroring what start() does for live Scapy packets.
        """
        features = self.traffic_analyzer.analyze_json_dict(msg)
        if not features:
            return

        # Push to Elasticsearch just like a live packet
        packet_doc = {
            'timestamp':        datetime.now(timezone.utc).isoformat(),
            'source_ip':        msg.get('source_ip'),
            'destination_ip':   msg.get('destination_ip'),
            'source_port':      msg.get('source_port'),
            'destination_port': msg.get('destination_port'),
            'packet_size':      msg.get('length'),
            'tcp_flags':        msg.get('tcp_flags'),
            'type':             'packet_json',
        }
        self.es_queue.put(("ids-packets", packet_doc))

        threats = self.detection_engine.detect_threats(features)
        for threat in threats:
            packet_info = {
                'source_ip':        msg.get('source_ip'),
                'destination_ip':   msg.get('destination_ip'),
                'source_port':      msg.get('source_port'),
                'destination_port': msg.get('destination_port'),
            }
            self.alert_system.generate_alert(threat, packet_info)

    def start(self):
        print(f"Starting IDS on interface {self.interface}")
        self.packet_capture.start_capture(self.interface)

        # Start the ES worker thread
        es_thread = threading.Thread(target=self._es_worker, daemon=True)
        es_thread.start()

        self.qt_bridge.start()

        while True:
            try:
                # --- Live Scapy packets ---
                try:
                    packet = self.packet_capture.packet_queue.get(timeout=0.1)
                    features = self.traffic_analyzer.analyze_packet(packet)

                    if features:
                        packet_doc = {
                            'timestamp':        datetime.now(timezone.utc).isoformat(),
                            'source_ip':        packet[IP].src,
                            'destination_ip':   packet[IP].dst,
                            'source_port':      packet[TCP].sport,
                            'destination_port': packet[TCP].dport,
                            'packet_size':      len(packet),
                            'tcp_flags':        int(packet[TCP].flags),
                            'type':             'packet'
                        }
                        #self.es_queue.put(("ids-packets", packet_doc))

                        threats = self.detection_engine.detect_threats(features)
                        for threat in threats:
                            packet_info = {
                                'source_ip':        packet[IP].src,
                                'destination_ip':   packet[IP].dst,
                                'source_port':      packet[TCP].sport,
                                'destination_port': packet[TCP].dport
                            }
                            #self.alert_system.generate_alert(threat, packet_info)

                except queue.Empty:
                    pass

                try:
                    msg = self.json_queue.get(timeout=0.1)
                    self._process_json_msg(msg)
                except queue.Empty:
                    pass

            except KeyboardInterrupt:
                print("Stopping IDS...")
                self.packet_capture.stop()
                self.qt_bridge.stop()
                self.es_queue.put((None, None))
                es_thread.join(timeout=5)
                break


if __name__ == "__main__":
    ids = IntrusionDetectionSystem()
    ids.start()
