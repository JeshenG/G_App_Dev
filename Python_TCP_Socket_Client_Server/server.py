import socket
import threading

#the first message that will be sent to the server should be 64 bytes
HEADER = 64 
PORT = 5050
#current device's IPv4 address: 192.168.56.1
SERVER = socket.gethostbyname(socket.gethostname()) 
ADDR = (SERVER,PORT)
FORMAT = 'utf-8'
DISCONNECT_MESSAGE = "DISCONNECT!"

#I added these globals, because threading.activeCount() is not working
thread_lock = threading.Lock() 
client_conn_count = 0 

#socket will open up a device to other connections
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDR)

#will handle the individual connections
def handle_client(conn, addr):
    global thread_lock
    global client_conn_count

    print(f"[NEW CONNECTION] {addr} Connected.")   
    connected = True

    """acquire and release the lock every time you increase your counter in your individual threads"""
    with thread_lock:
        client_conn_count += 1 

    while connected:
        #receive info from client, first get message length  
        msg_length = conn.recv(HEADER).decode(FORMAT)
        #check if message is not None
        if(msg_length):
            msg_length = int(msg_length)
            msg = conn.recv(msg_length).decode(FORMAT)
            if(msg == DISCONNECT_MESSAGE):
                connected = False
                #I added in this global lock code 
                with thread_lock:
                   client_conn_count -= 1 

            print(f"[{addr}] {msg}")

            #send message back to the client 
            conn.send("Msg received".encode(FORMAT))

    conn.close()

def start():
    global client_conn_count

    server.listen()
    print(f"[LISTENING] Server is listening on {SERVER}")
    while True:
        conn,addr = server.accept()
        #when a new connection occurs, pass it to handle_client
        thread = threading.Thread(target=handle_client, args=(conn,addr)) 
        thread.start()
        #print(f"[ACTIVE CONNECTIONS] {threading.activeCount() - 1}") #Returning wrong active connection count???
        print(f"[ACTIVE CONNECTIONS] {client_conn_count + 1}")

print("[STARTING] Server is starting...")
start()


