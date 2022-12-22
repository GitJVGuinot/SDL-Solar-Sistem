/// @File servidor_tcp.c

#include <iostream>
#include <vector>
#include <winsock.h>

#pragma comment(lib, "ws2_32.lib")

#define MYPORT 9999
#define BUFLEN 512
#define MAX_CLIENTS 2
#define WAIT_TIME 2
#define CLOSE_TIME WAIT_TIME*10

int main()
{
  system("cls");
  system("title Solar System Server");

  WSADATA ws;
  if(WSAStartup(MAKEWORD(2, 0), &ws) != 0) {
    printf("WSAStartup() failed with error code: %d", WSAGetLastError());
    return 1;
  }
  printf("Initialised.\n");

  SOCKET sock_in;
  std::vector<SOCKET> sock_clients;
  std::cout << "Vec capacity: " << sock_clients.capacity() << std::endl;
  if((sock_in = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR) {
    printf("socket() failed with error code: %d", WSAGetLastError());
    return 1;
  }

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(MYPORT);

  if(bind(sock_in,(SOCKADDR*)&server, sizeof(server)) == SOCKET_ERROR){
    printf("bind() failed with error code: %d", WSAGetLastError());
    return 1;
  }

  if(listen(sock_in, SOMAXCONN) == SOCKET_ERROR) {
    printf("listen() failed with error code: %d", WSAGetLastError());
    return 1;
  }

  int current_clients = 0;
  fd_set fdin;
  struct timeval tv;  // Time to wait in secs and micro secs
  tv.tv_sec = 2;      // sec to wait
  tv.tv_usec = 0;     // micro secs to wait

  char buffer[BUFLEN];
  int cont = CLOSE_TIME;
  while(current_clients > 0 || cont > 0) {

    FD_ZERO(&fdin);
    FD_SET(sock_in, &fdin);

    // Monitorizo clientes ya conectados.
    for(int i = 0; i < current_clients; i++) {
      if(sock_clients.at(i) > 0) {
        FD_SET(sock_clients.at(i), &fdin);
      }
    }

    if(select(current_clients, &fdin, NULL, NULL, &tv) != 0) {

      // Comprobar nuevas conexiones.
      if(FD_ISSET(sock_in, &fdin) && current_clients < MAX_CLIENTS) {
        cont = CLOSE_TIME;
        sock_clients.push_back(accept(sock_in, NULL, NULL));
        recv(sock_clients.at(current_clients), buffer, BUFLEN, 0);
        current_clients++;
        printf("New client. Current clients: %d\n", current_clients);
      }

        // Gestiona las conexiones
        for(int i = 0; i < current_clients; i++) {
          if(FD_ISSET(sock_clients.at(i), &fdin)) {

            memset(buffer, 0, BUFLEN);
            if(recv(sock_clients.at(i), buffer, BUFLEN, 0) > 0) {
              printf("Recibed: %s\n", buffer);
            } else {
              closesocket(sock_clients.at(i));
              sock_clients.erase(sock_clients.begin()+i);
              current_clients--;
              printf("Desconexion. Current_clients: %d\n", current_clients);
              if(current_clients==0)
                printf("No clients connected waiting %ds to close\n", cont);
            }
          }
        }
    }
    if(current_clients <= 0){ cont-=WAIT_TIME; printf("Time to close: %ds\n", cont); }
  }

  sock_clients.clear();
  printf("Closing server\n");
  system("pause");
  return 0;
}
