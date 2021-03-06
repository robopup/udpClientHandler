/*
CLIENT: SERVER MUST BE STARTED FIRST
*/

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <Windows.h>
#include <WinSock2.h>
#include <iphlpapi.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")			// Winsock library

using namespace std;

int main()
{

	// Initialize Winsock:
	WSADATA WSAData;
	printf("Initializing Winsock...\n\r");
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
	{
		printf("Failed. Error Code: %d", WSAGetLastError());
		return 1;
	}
	printf("Winsock initialized.\n\r");

	// Open a socket to the server:
	SOCKET server;
	SOCKADDR_IN addr;
	if ((server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
	} // may wish to change IPPROTO_UDP to 0, for no protocol specify
	printf("Socket created.\n\r");

	addr.sin_addr.s_addr = inet_addr("172.16.3.162");			// place IP address of server program
	addr.sin_family = AF_INET;
	addr.sin_port = htons(11000);								// port #
	if (connect(server, (SOCKADDR *)&addr, sizeof(addr)) < 0) {
		puts("Connection error");
		return 1;
	}
	printf("Connected.\n\r");

	// Send some data:
	char *message;
	message = "Hello World: message passed successfully.";
	if (send(server, message, strlen(message), 0) < 0) {
		puts("Send failed.");
		return 1;
	}
	printf("Data sent.\n\r");

	// Exit routine
	closesocket(server);
	WSACleanup();
	printf("Press enter to continue/exit()\n\r");
	getchar();

	return 0;
}