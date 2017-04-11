import socket , sys	#import socket package and sys
port = 80				# port for UDP (8888 udp default)
s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)	#create socket (DGRAM for UDP)
host=socket.gethostbyname( '0.0.0.0' )						#get the IP server
s.bind((host,port))												#make connection
while True:
    data, addr = s.recvfrom(1024)							#recieve data from client
    print data														#print data
    if not data:													#not data break
        break
s.close()															#closing connection
sys.exit()	
