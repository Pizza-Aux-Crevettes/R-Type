/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.cpp
*/

#include "socket/Server.hpp"
#include "util/Logger.hpp"
#include <SmartBuffer.hpp>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

UdpSocket::UdpSocket() : _udpSocket(FAILURE) {
    Logger::socket("[UDP Socket] Instance created for port: " +
                   std::to_string(PORT));
}

UdpSocket::~UdpSocket() {
    Logger::socket("[UDP Socket] Instance for port " + std::to_string(PORT) +
                   " is being destroyed.");
    close();
}

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

            Server::getProtocol().handleMessage(_udpSocket, smartBuffer);
        } else {
            Logger::warning("[UDP Socket] Failed to receive data from client.");
        }
    }
}

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
