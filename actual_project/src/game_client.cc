/// @author Javier guinot Almenar <guinotal@esat-alumni.com>
/// @file game_client.cc

#include <game_client.h>

GameClient::GameClient()
{
#ifdef _WIN32
  WSADATA wsaData;
  WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

  m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

GameClient::~GameClient()
{
#ifdef _WIN32
  closesocket(m_socket);
  WSACleanup();
#elif __linux__
  close(m_socket);
#endif
}

void GameClient::connectToServer(const std::string &ipAddress, int port)
{
  sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
#ifdef _WIN32
  serverAddr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
#elif __linux__
  inet_aton(ipAddress.c_str(), &serverAddr.sin_addr);
#endif

  connect(m_socket, (sockaddr *)&serverAddr, sizeof(serverAddr));
}

void GameClient::sendReceive()
{
  while (true)
  {
    char buffer[1024];
    int bytesReceived = recv(m_socket, buffer, 1024, 0);
    if (bytesReceived > 0)
    {
      std::cout << "Buffer: " << buffer << std::endl;
    }

    // Enviar un mensaje al servidor
    std::string message = "Hello from client!";
    send(m_socket, message.c_str(), message.size() + 1, 0);
  }
}
