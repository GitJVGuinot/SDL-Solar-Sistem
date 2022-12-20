/// @File cliente_tcp.c

#include <iostream>
#include <winsock.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER "127.0.0.1"  // or "localhost" - ip address of server
#define BUFLEN 512  				// max length of answer
#define SERVERPORT 9999 		// the port on which to listen for incoming data

int main()
{
  system("cls");
  system("title Solar System Client");

  WSADATA ws;
  if(WSAStartup(MAKEWORD(2, 0), &ws) != 0)
  {
      printf("WSAStartup() failed with error code: %d", WSAGetLastError());
      return 1;
  }
  printf("Initialised.\n");

  SOCKET sock;
  if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR) // <<< TCP socket
  {
      printf("socket() failed with error code: %d", WSAGetLastError());
      return 1;
  }

  struct sockaddr_in cliente;
  cliente.sin_family = AF_INET;
  cliente.sin_port = htons(SERVERPORT);
  cliente.sin_addr.S_un.S_addr = inet_addr(SERVER);

  if(connect(sock,(SOCKADDR*)&cliente, sizeof(cliente)) == SOCKET_ERROR) // <<< TCP socket
  {
      printf("connect() failed with error code: %d\n", WSAGetLastError());
      return 1;
  }

  char buffer[BUFLEN] = "New Connection\0";
  while(strcmp(buffer, "Adios")) {

    if(send(sock, buffer, strlen(buffer), 0) == SOCKET_ERROR) // <<< TCP socket
    {
        printf("socket() failed with error code: %d", WSAGetLastError());
    }

    memset(buffer, 0, BUFLEN);
    printf("Message: ");
    std::cin.getline(buffer, BUFLEN);
  }

  system("pause");
  return 0;
}
