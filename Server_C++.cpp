#include <winsock2.h>					//socket library for windows
#include <stdlib.h>
#include	<stdio.h>
 
#pragma comment(lib,"ws2_32.lib")	//Winsock Library
 
#define BUFLEN 800						//Max length of buffer
#define PORT 80   						//Port for UDP (default 8888)
 
int main()
{
   SOCKET s;										// socket object
   struct sockaddr_in server, si_other;	// socket server and client
   int slen ,recv_len;							// len server - client
   char buf[BUFLEN];								// buffer (recieved data)
	char msg[BUFLEN]="Hello client"; 		// buffer (sent data)
   WSADATA wsa;									// WSA object 
      
   //Initialise winsock
   printf("\nInitialising Winsock...");
   
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
   	{
        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    	}
   
	printf("Initialised.\n");
     
   //Create a socket
   if((s = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET)
   	{
        printf("Could not create socket : %d" , WSAGetLastError());
   	}
   
	printf("Socket created.\n");
     
   //Prepare the sockaddr_in structure
   server.sin_family = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port = htons( PORT );
   slen = sizeof(si_other);					
    
   //Bind
   if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
   	{
        printf("Bind failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
   	}
   
	puts("Bind done");
 
   //keep listening for data
   while(1)
   	{
      	printf("Waiting for data...");
        	fflush(stdout);
         
        	//clear the buffer by filling null
        	memset(buf,'\0', BUFLEN);
         
        	//try to receive some data
        	if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
        		{
            	printf("recvfrom() failed with error code : %d" , WSAGetLastError());
            	exit(EXIT_FAILURE);
        		}
         
        	//print details of the client and data received
       	printf("Received data from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        	printf("Data: %s\n" , buf);
         
        	//now reply the client
        	if (sendto(s, msg, strlen(msg), 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
        		{
            	printf("sendto() failed with error code : %d" , WSAGetLastError());
            	exit(EXIT_FAILURE);
        		}
    	}
 
   closesocket(s);	//close socket connection
   WSACleanup();		//clean the WSA
     
   return 0;
}