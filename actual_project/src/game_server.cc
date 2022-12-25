/// @author Javier guinot Almenar <guinotal@esat-alumni.com>
/// @file game_server.cc

#include <game_server.h>

GameServer::GameServer()
{
#ifdef _WIN32
  WSADATA wsaData;
  WSAStartup(MAKEWORD(2, 2), &wsaData);
#elif __linux__

#endif

  m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(12345);
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  bind(m_socket, (sockaddr *)&serverAddr, sizeof(serverAddr));
  listen(m_socket, SOMAXCONN);
}

GameServer::~GameServer()
{
#ifdef _WIN32
  closesocket(m_socket);
  WSACleanup();
#elif __linux__
  close(m_socket);
#endif
}

void GameServer::listenForConnections()
{
  while (true)
  {
    sockaddr_in clientAddr;
#ifdef _WIN32
    int clientAddrSize = sizeof(clientAddr);
    SOCKET clientSocket = accept(m_socket, (sockaddr *)&clientAddr, &clientAddrSize);
#elif __linux__
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(m_socket, (sockaddr *)&clientAddr, &clientAddrSize);
#endif

    Client client;
    client.socket = clientSocket;
    client.address = clientAddr;
    m_clients.push_back(client);
  }
}

void GameServer::sendReceive()
{
  while (true)
  {
    for (int i = 0; i < (int)m_clients.size(); i++)
    {
      Client &client = m_clients[i];
      char buffer[1024];
      int bytesReceived = recv(client.socket, buffer, 1024, 0);
      if (bytesReceived > 0)
      {
        std::cout << "Buffer: " << buffer << std::endl;
      }
    }
  }
}
