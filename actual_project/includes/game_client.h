/// @author Javier guinot Almenar <guinotal@esat-alumni.com>
/// @file game_client.h

////////////////////////
#ifndef __GAME_CLIENT_H__
#define __GAME_CLIENT_H__
////////////////////////

#include <iostream>
#ifdef _WIN32
#include <winsock2.h>
#include <string>
#elif __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#endif

/**
 * @brief A class for connecting to a game server and sending/receiving data.
 */
class GameClient
{
public:
  /**
   * @brief Constructor for the GameClient class.
   */
  GameClient();

  /**
   * @brief Destructor for the GameClient class.
   */
  ~GameClient();

  /**
   * @brief Connects to a game server at the specified IP address and port.
   *
   * @param ipAddress The IP address of the game server.
   * @param port The port number of the game server.
   */
  void connectToServer(const std::string &ipAddress, int port);

  /**
   * @brief Sends data to and receives data from the game server.
   */
  void sendReceive();

private:
#ifdef _WIN32
  SOCKET m_socket; ///< The socket descriptor for the connection to the game server (Windows).
#elif __linux__
  int m_socket; ///< The socket descriptor for the connection to the game server (Linux).
#endif
};

////////////////////////
#endif /* __GAME_CLIENT_H__ */
////////////////////////
