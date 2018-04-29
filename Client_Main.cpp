#include<iostream>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#include<string>

using namespace std;

int main() {
	string ipAdress = "127.0.0.1";
	int port = 54000;

	//initialize winsock

	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0) {
		cerr << "Can't start winsock, err #" << wsResult << endl;
		return 0;
	}


	//create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET) {
		cerr << "Can't create socket,Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}

	//fill structure

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAdress.c_str(), &hint.sin_addr);

	//connect to server

	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));

	if (connResult == SOCKET_ERROR) {
		cerr << "Can't connect to server, err#" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return 0;
	}

	//do-while to send and recive data

	char buf[4096];
	string userInput;
	do {
		//promt the user for text
		cout << "> ";
		getline(cin, userInput);

		if (userInput.size() > 0) { //make sure there is user input
									//send text
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);

			if (sendResult != SOCKET_ERROR) {


				//wait for response
				ZeroMemory(buf, 4096);
				int bytesRecived = recv(sock, buf, 4096, 0);

				if (bytesRecived > 0) {
					//echo response for console
					cout << "SERVER>" << string(buf, 0, bytesRecived) << endl;
				}
			}
		}
	} while (userInput.size() > 0);

	// close down everything
	closesocket(sock);
	WSACleanup();

}
