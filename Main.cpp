#include<iostream>
#include<WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")
#include<string>
using namespace std;


int main() {

	// Initialize winsock

	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	int wsOK = WSAStartup(ver, &wsData);
	if (wsOK != 0) {
		cerr << "Can't initialize winsock! Quitting" << endl;
		return 0;
	}


	// Create a socket

	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		cerr << "Can't create a socket! Quitting" << endl;
		return 0;
	}



	// Bind   IP adress & port to socket

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	//Tell Winsock the socket is for listening

	listen(listening, SOMAXCONN);


	//Wait for connection

	sockaddr_in client;
	int clientSize = sizeof(client);
	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
	if (clientSocket == INVALID_SOCKET) {
		cerr << "invalid client socket! Quitting" << endl;
	}

	char host[NI_MAXHOST]; //client remote name
	char service[NI_MAXSERV];//service(port) that client is connected on

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0){
		cout << host << " connected on port " << service << endl;
		}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port " << ntohs(client.sin_port) << endl;
	}

	// Close listening socket

	closesocket(listening);
	
	
	// While loop : accept and echo message back to Client

	char buf[4096];

	while (true) {
		ZeroMemory(buf, 4096);
		//wait for client to send data
		

		int bytesRecived = recv(clientSocket, buf, 4096, 0);

		/*-------------
		if (bytesRecived == 0) {
			cout << "The connection is off";
		}
		if (bytesRecived == -1) {
			cout << "There is a problem with the connection";
		}
		if (bytesRecived > 0) {
			cout << "The connection is on";
		}
		//-----------*/
		if (bytesRecived == SOCKET_ERROR) {
			cerr << "Error in recv(). Quitting" << endl;
			break;
		}

		if (bytesRecived == 0) {
			cout << "Client disconnected " << endl;
			break;
		}

		cout << string(buf, 0, bytesRecived) << endl;

		//echo message back to client
		send(clientSocket, buf, bytesRecived + 1, 0);
	}


	
	// Close socket

	closesocket(clientSocket);

	// Cleanup winsock
	WSACleanup();

}


