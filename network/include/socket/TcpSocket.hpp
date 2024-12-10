/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.hpp
*/

#include <netinet/in.h>
#include <thread>
#include <vector>

/**
 * @class TcpSocket
 * @brief Provides functionality for managing TCP socket operations.
 *
 * This class handles initialization, accepting connections, sending, receiving,
 * and managing client threads for TCP sockets.
 */
class TcpSocket {
  public:
    /**
     * @brief Constructs a new TcpSocket instance.
     *
     * Initializes internal variables and prepares the socket instance.
     */
    TcpSocket();

    /**
     * @brief Destructs the TcpSocket instance.
     *
     * Ensures all threads and the socket are properly closed and cleaned up.
     */
    ~TcpSocket();

    /**
     * @brief Sends data via TCP to a specified client socket.
     *
     * @param clientSocket The socket descriptor for the client.
     * @param smartBuffer A reference to the SmartBuffer containing the data to
     * send.
     */
    static void sendTcp(int clientSocket, SmartBuffer& smartBuffer);

    /**
     * @brief Initializes the TCP socket.
     *
     * Creates a socket, binds it to the specified port, and prepares it for
     * listening.
     *
     * @throws std::runtime_error if the socket creation, binding, or listening
     * fails.
     */
    void init();

    /**
     * @brief Listens for incoming TCP connections.
     *
     * Accepts client connections and starts a new thread to handle each client.
     */
    void listen();

    /**
     * @brief Closes the TCP socket and joins all client threads.
     *
     * Ensures that all resources are properly released.
     */
    void close();

  private:
    int _tcpSocket;       ///< The file descriptor for the TCP socket.
    sockaddr_in _tcpAddr; ///< The address structure for the TCP socket.
    std::vector<std::thread>
        _clientThreads; ///< Vector of threads handling connected clients.

    /**
     * @brief Handles communication with a single client.
     *
     * This method is executed in a separate thread for each client connection.
     *
     * @param clientSocket The socket descriptor for the connected client.
     */
    void handleClient(int clientSocket);
};
