/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.hpp
*/

/**
 * @file UdpSocket.hpp
 * @brief Declaration of the UdpSocket class for managing UDP socket
 * communication.
 */

#pragma once

#include <SmartBuffer.hpp>
#include <netinet/in.h>

/**
 * @class UdpSocket
 * @brief Provides functionality for managing UDP socket operations.
 *
 * This class handles initialization, sending, receiving, and closing of UDP
 * sockets.
 */
class UdpSocket {
  public:
    /**
     * @brief Constructs a new UdpSocket instance.
     *
     * Initializes internal variables and prepares the socket instance.
     */
    UdpSocket();

    /**
     * @brief Destructs the UdpSocket instance.
     *
     * Ensures the socket is properly closed if it hasn't already been closed.
     */
    ~UdpSocket();

    /**
     * @brief Sends data via UDP to the specified client address.
     *
     * @param udpSocket The socket descriptor used for sending the data.
     * @param clientAddr The sockaddr_in structure containing the client's
     * address.
     * @param smartBuffer A reference to the SmartBuffer containing the data to
     * send.
     */
    static void sendUdp(int udpSocket, const sockaddr_in& clientAddr,
                        SmartBuffer& smartBuffer);

    /**
     * @brief Initializes the UDP socket.
     *
     * Creates a socket, binds it to the specified port, and prepares it for
     * listening.
     *
     * @throws std::runtime_error if the socket creation or binding fails.
     */
    void init();

    /**
     * @brief Listens for incoming UDP messages.
     *
     * Receives data packets, processes them, and forwards them to the
     * appropriate handler. This method runs in a loop and should typically be
     * executed on a separate thread.
     */
    void listen();

    /**
     * @brief Closes the UDP socket.
     *
     * Ensures the socket is properly closed and releases any associated
     * resources.
     */
    void close();

  private:
    int _udpSocket;       ///< The file descriptor for the UDP socket.
    sockaddr_in _udpAddr; ///< The address structure for the UDP socket.
};
