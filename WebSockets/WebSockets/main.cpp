#include <iostream>
#include <winsock.h>
#include <string.h>
#include <windows.h>

using namespace std;
#pragma comment(lib, "ws2_32.lib")


int main(void)
{
	// Initialize Winsock
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cerr << "WSAStartup failed\n";
		return 0;
	}

	// Creat socket
	int listeningSocket;
	int clientSocket;
	listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listeningSocket == -1)
	{
		cerr << "can not creat socket\n";
		return 0;
	}
	// Bind the socket with ip address and port number
	sockaddr_in server;
	sockaddr_in client;

	server.sin_family = AF_INET;
	server.sin_port = htons(8080);
	server.sin_addr.s_addr = INADDR_ANY;
	memset(server.sin_zero, 8, 0);

	int len = sizeof(sockaddr_in);

	if (bind(listeningSocket, (sockaddr*)&server, sizeof(server)) == -1)
	{
		cerr << "can not listen";
		return 0;
	}

	// Start listening

	if (-1 == (listen(listeningSocket, 5)))
	{
		cerr << "Can not listen\n";
		return 0;
	}

	// wait for the connection

	if ((clientSocket = accept(listeningSocket, (sockaddr*)&client, &len)) == -1)
	{
		cerr << "can not accept";
		return 0;
	}

	//close the listeningSocket
	closesocket(listeningSocket);

	// while loop: send/rec messages
	char buff[4096];
	string msg;

	while (true)
	{
		// wait for the client to send the message
		memset(buff, 4096, 0);
		int bytesReceived = recv(clientSocket, buff, 4096, 0);
		if (bytesReceived > 0)
		{   

			///print back messages to the client
			int sent = send(clientSocket, buff, bytesReceived, 0);
			cout << "sent " << sent << "bytes to client" << inet_ntoa(client.sin_addr) << endl;
		}
	}

	//close socket
	closesocket(listeningSocket);


	return 0;
}





