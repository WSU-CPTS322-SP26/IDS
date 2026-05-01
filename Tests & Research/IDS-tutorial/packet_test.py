import socket, json, time

msgs = [{'source_ip': '10.10.10.10', 'destination_ip': '10.0.0.1', 'source_port': 9000+i, 'destination_port': 80, 'length': 44, 'tcp_flags': 2, 'protocol': 'TCP', 'timestamp': '2026-04-30T12:00:00Z'} for i in range(10)] + [{'source_ip': '172.16.0.99', 'destination_ip': '10.0.0.1', 'source_port': 12345, 'destination_port': 1000+i, 'length': 44, 'tcp_flags': 2, 'protocol': 'TCP', 'timestamp': '2026-04-30T12:00:00Z'} for i in range(8)]

s = socket.create_connection(('127.0.0.1', 9999))
for m in msgs:
    s.sendall((json.dumps(m)+'\n').encode())
    time.sleep(0.01)
print('Done')