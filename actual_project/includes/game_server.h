/// @author Javier guinot Almenar <guinotal@esat-alumni.com>
/// @file game_server.h

////////////////////////
#ifndef __GAME_SERVER_H__
#define __GAME_SERVER_H__
////////////////////////

#include <iostream>

#ifdef _WIN32
#include <winsock2.h>
#include <vector>
#elif __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <unistd.h>
#endif

/**
 * @brief A structure representing a client connected to the game server.
 */
struct Client
{
#ifdef _WIN32
  SOCKET socket; ///< The socket descriptor for the connection to the client (Windows).
#elif __linux__
  int socket; ///< The socket descriptor for the connection to the client (Linux).
#endif
  sockaddr_in address; ///< The address of the client.
};

/**
 * @brief A class for listening for connections and sending/receiving data on a game server.
 */
class GameServer
{
public:
  /**
   * @brief Constructor for the GameServer class.
   */
  GameServer();

  /**
   * @brief Destructor for the GameServer class.
   */
  ~GameServer();

  /**
   * @brief Listens for incoming connections and adds them to a list of clients.
   */
  void listenForConnections();

  /**
   * @brief Sends data to and receives data from the clients.
   */
  void sendReceive();

private:
#ifdef _WIN32
  SOCKET m_socket; ///< The socket descriptor for the server (Windows).
#elif __linux__
  int m_socket; ///< The socket descriptor for the server (Linux).
#endif
  std::vector<Client> m_clients; ///< A list of clients connected to the server.
};

////////////////////////
#endif /* __GAME_SERVER_H__ */
////////////////////////
