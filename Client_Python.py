import socket                   # Import socket module

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)             # Create a socket object (DGRAM FOR UDP)
host = '192.168.4.51'     	# IP server
port = 80                  # Reserve a port for your (UDP 8888 default)
s.connect((host,port))		# Connection with the server
while True:
    s.send("Hello World!")	#Send something to server

    data=s.recv(1024)		#recieving the data from server
    print (data)				#print data
