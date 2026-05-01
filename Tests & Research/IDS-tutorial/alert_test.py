import socket, json

s = socket.create_connection(('127.0.0.1', 9999))
print('Listening for alerts...')
buf = ''
while True:
    chunk = s.recv(4096).decode()
    buf += chunk
    while '\n' in buf:
        line, buf = buf.split('\n', 1)
        print('ALERT:', json.loads(line))