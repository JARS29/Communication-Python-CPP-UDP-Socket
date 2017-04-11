// sentdata.cpp : Defines the entry point for the console application.
//

#include <windows.h>		
#include <winsock2.h>	//socket windows
#include <ws2tcpip.h>	//tcpip library
#include <stdlib.h>
#include <stdio.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define BUFLEN 800						//Max length of buffer
#define PORT 80							//Max length of buffer
#define SERVER "192.168.4.49"			//Port for UDP (default 8888)

int main() 
{
  	WSADATA wsa;										//WSA object 
	struct sockaddr_in si_other;					//struct client
	int s, slen=sizeof(si_other);					//len client
	char buf[BUFLEN];									//buffer (recieved data)
	char const msg[BUFLEN]="Hello server!";	//buffer (sent data)

	//Initialise winsock
	printf("\nInitialising Winsock...");
	
	if(WSAStartup(MAKEWORD(2,2), &wsa) !=0)
	{
		printf("Failed WSA. EC: %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	
	//Create a socket
	printf("nInitialising Socket...\n");
     
   if((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("Failed SOCKET. EC: %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	
	printf("Socket created.\n");
	
	//Prepare the sockaddr_in structure
	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
	
	
	//keep sending data
	while(1)
	{
		if(sendto(s, msg , strlen(msg), 0, (struct sockaddr *)&si_other, slen) == SOCKET_ERROR)
		{
			printf("Failed sendto. EC: %d",WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}
 
   closesocket(s);	//close connection
   WSACleanup();		//clean wsa

   return 0;
}