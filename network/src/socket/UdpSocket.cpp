/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.cpp
*/

/**
 * @file UdpSocket.cpp
 * @brief Implements the UdpSocket class for handling UDP communication.
 */

#include "socket/UdpSocket.hpp"
#include "util/Logger.hpp"
#include "util/Singletons.hpp"
#include <SmartBuffer.hpp>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

/**
 * @brief Constructs a UdpSocket instance and initializes internal variables.
 */
UdpSocket::UdpSocket() : _udpSocket(FAILURE) {
    Logger::socket("[UDP Socket] Instance created for port: " +
                   std::to_string(PORT));
}

/**
 * @brief Destroys the UdpSocket instance, closing any open connections.
 */
UdpSocket::~UdpSocket() {
    Logger::socket("[UDP Socket] Instance for port " + std::to_string(PORT) +
                   " is being destroyed.");

    close();
}

/**
 * @brief Sends a UDP packet to a specified client.
 * @param udpSocket The socket to send data from.
 * @param clientAddr The destination client's address.
 * @param smartBuffer The data to send, encapsulated in a SmartBuffer.
 */
void UdpSocket::sendUdp(int udpSocket, const sockaddr_in& clientAddr,
                        SmartBuffer& smartBuffer) {
    ssize_t bytesSent =
        sendto(udpSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0,
               (struct sockaddr*)&clientAddr, sizeof(clientAddr));

    if (bytesSent < 0) {
        Logger::error("[Socket] UDP send failed for UDP socket: " +
                      std::to_string(udpSocket));
    } else {
        Logger::info("[Socket] UDP send succeeded. Bytes sent: " +
                     std::to_string(bytesSent));
    }
}

/**
 * @brief Initializes the UDP socket, binding it to a port.
 * @throws std::runtime_error If the socket fails to initialize or bind.
 */
void UdpSocket::init() {
    Logger::socket("[UDP Socket] Initializing socket on port: " +
                   std::to_string(PORT));

    _udpSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (_udpSocket == FAILURE) {
        Logger::error("[UDP Socket] Failed to create socket.");

        throw std::runtime_error("Failed to create UDP socket.");
    }

    _udpAddr.sin_family = AF_INET;
    _udpAddr.sin_addr.s_addr = INADDR_ANY;
    _udpAddr.sin_port = htons(PORT);

    if (bind(_udpSocket, (struct sockaddr*)&_udpAddr, sizeof(_udpAddr)) <
        SUCCESS) {
        Logger::error("[UDP Socket] Failed to bind socket to port: " +
                      std::to_string(PORT));

        throw std::runtime_error("Bind failed for UDP socket on port " +
                                 std::to_string(PORT));
    }

    Logger::socket("[UDP Socket] Successfully bound to port: " +
                   std::to_string(PORT));
}

/**
 * @brief Continuously listens for incoming UDP messages.
 * Forwards received data to the protocol handler for processing.
 */
void UdpSocket::listen() {
    SmartBuffer smartBuffer;
    sockaddr_in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    Logger::socket("[UDP Socket] Listening for incoming messages on port: " +
                   std::to_string(PORT));

    while (true) {
        char rawBuffer[1024] = {0};
        int bytesRead = recvfrom(_udpSocket, rawBuffer, sizeof(rawBuffer), 0,
                                 (struct sockaddr*)&clientAddr, &addrLen);

        if (bytesRead > 0) {
            Logger::packet("[UDP Socket] Received " +
                           std::to_string(bytesRead) + " bytes from " +
                           inet_ntoa(clientAddr.sin_addr) + ":" +
                           std::to_string(ntohs(clientAddr.sin_port)));

            smartBuffer.inject(reinterpret_cast<const uint8_t*>(rawBuffer),
                               bytesRead);
            smartBuffer.resetRead();

            Singletons::getProtocol().handleMessage(_udpSocket, smartBuffer);
        } else {
            Logger::warning("[UDP Socket] Failed to receive data from client.");
        }
    }
}

/**
 * @brief Closes the UDP socket, releasing associated resources.
 */
void UdpSocket::close() {
    if (_udpSocket != FAILURE) {
        ::close(_udpSocket);

        Logger::socket("[UDP Socket] Socket on port " + std::to_string(PORT) +
                       " successfully closed.");
    } else {
        Logger::warning("[UDP Socket] Attempted to close an uninitialized or "
                        "already closed socket.");
    }
}
