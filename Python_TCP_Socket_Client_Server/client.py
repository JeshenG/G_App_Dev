import socket

#the first message that will be sent to the server should be 64 bytes
HEADER = 64 
PORT = 5050
FORMAT = 'utf-8'
DISCONNECT_MESSAGE = "DISCONNECT!"
SERVER = "192.168.56.1"
ADDR = (SERVER,PORT)

client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
client.connect(ADDR)

def send(msg):
    message = msg.encode(FORMAT)
    msg_length = len(message)
    send_length = str(msg_length).encode(FORMAT)
    #padding send length 
    send_length += b' ' * (HEADER - len(send_length))
    client.send(send_length)
    client.send(message)
    
    print(client.recv(2048).decode(FORMAT))

send("Hello World!")
input()
send("Hello Dr!")
input()
send("Hello Everyone!")
input()
send("Hello G!")

send(DISCONNECT_MESSAGE)
