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
            'packet_count' : stats['packet_count'],
            'source_ip' : packet[IP].src
        }
    


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


                    # test func perameters
                    # features['tcp_flags'] == 2 and
                    # features['packet_rate'] > 5 and
                    # features['packet_size'] < 100 and
                    # features['packet_count'] > 1


                    # real data parameters
                    # features['packet_rate'] > 5000 and
                    # features['flow_duration'] > 0.01

                )
            },
            'port_scan': {
                'condition': lambda features: (
                    len(self.traffic_analyzer.port_hits[features['source_ip']]) >= 5 and
                    features['packet_rate'] > 100 and
                    features['flow_duration'] > 0.01


                    # test func perameters
                    # len(self.traffic_analyzer.port_hits[features['source_ip']]) >= 3
                    # features['packet_size'] < 80 and
                    # features['packet_rate'] > 50 and
                    # features['packet_size'] < 100 and
                    # features['packet_count'] > 1

                    #real data parametrs
                    # features['packet_rate'] > 8000 and
                    # features['flow_duration'] > 0.02

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
        if anomaly_score < -0.5:  # Threshold for anomaly detection
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
    def __init__(self, log_file="ids_alerts.log",es_url=None):
        self.es_url = es_url
        self.logger = logging.getLogger("IDS_Alerts")
        self.logger.setLevel(logging.INFO)

        handler = logging.FileHandler(log_file)
        formatter = logging.Formatter(
            '%(asctime)s - %(levelname)s - %(message)s'
        )
        handler.setFormatter(formatter)
        self.logger.addHandler(handler)

    def send_to_elasticsearch(self, alert):
        if not self.es_url:
            return
        try:
            requests.post(
                f"{self.es_url}/ids-alerts/_doc",
                json=alert,
                timeout=2
            )
        
        except Exception as e:
            print(f"Failed to send alert to Elasticsearch: {e}")

    def generate_alert(self, threat, packet_info):
        alert = {
            'timestamp': datetime.now(timezone.utc).isoformat(),
            'threat_type': threat['type'],
            'source_ip': packet_info.get('source_ip'),
            'destination_ip': packet_info.get('destination_ip'),
            'confidence': threat.get('confidence', 0.0),
            'details': threat
        }

        self.logger.warning(json.dumps(alert))
        self.send_to_elasticsearch(alert)

        if threat['confidence'] > 0.8:
            self.logger.critical(
                f"High confidence threat detected: {json.dumps(alert)}"
            )
            # Implement additional notification methods here
            # (e.g., email, Slack, SIEM integration)

import os
import socket
from scapy.all import get_if_list, get_if_addr


class IntrusionDetectionSystem:
    def __init__(self, interface=None):
        if interface is None:
            interface = self.auto_select_interface()

        self.packet_capture = PacketCapture()
        self.traffic_analyzer = TrafficAnalyzer()
        self.detection_engine = DetectionEngine(self.traffic_analyzer)
        es_url = os.getenv("ES_URL", "http://localhost:9200")
        self.alert_system = AlertSystem(es_url=es_url)

        self.detection_engine.train_anomaly_detector([[50, 1, 100]])
        self.interface = interface


    def auto_select_interface(self):
        # Step 1: Ask OS which local IP is used for outbound traffic
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        try:
            s.connect(("8.8.8.8", 80))
            local_ip = s.getsockname()[0]
        finally:
            s.close()

        # Step 2: Match that IP to a Scapy interface
        for iface in get_if_list():
            try:
                iface_ip = get_if_addr(iface)
                if iface_ip == local_ip:
                    return iface
            except:
                continue

        # Step 3: Fallback — skip virtual adapters
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



    def start(self):
        print(f"Starting IDS on interface {self.interface}")
        self.packet_capture.start_capture(self.interface)

        while True:
            try:
                packet = self.packet_capture.packet_queue.get(timeout=1)
                features = self.traffic_analyzer.analyze_packet(packet)

                if features:

                    packet_doc = {
                        'timestamp': datetime.now(timezone.utc).isoformat(),
                        'source_ip': packet[IP].src,
                        'destination_ip': packet[IP].dst,
                        'source_port': packet[TCP].sport,
                        'destination_port': packet[TCP].dport,
                        'packet_size': len(packet),
                        'tcp_flags': int(packet[TCP].flags),
                        'type': 'packet'
                    }

                    try:
                        r = requests.post(
                            f"{self.alert_system.es_url}/ids-packets/_doc",
                            json=packet_doc,
                            timeout=2
                        )
                    except Exception as e:
                        print("Packet indexing error:", e)

                    threats = self.detection_engine.detect_threats(features)

                    for threat in threats:
                        packet_info = {
                            'source_ip': packet[IP].src,
                            'destination_ip': packet[IP].dst,
                            'source_port': packet[TCP].sport,
                            'destination_port': packet[TCP].dport
                        }
                        self.alert_system.generate_alert(threat, packet_info)

            except queue.Empty:
                continue
            except KeyboardInterrupt:
                print("Stopping IDS...")
                self.packet_capture.stop()
                break

if __name__ == "__main__":
    ids = IntrusionDetectionSystem()
    ids.start()
