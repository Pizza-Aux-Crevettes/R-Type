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

UdpSocket::UdpSocket(Config port) : port(port), udpSocket(FAILURE) {
    Logger::socket("[UDP Socket] Instance created for port: " +
                   std::to_string(port));
}

UdpSocket::~UdpSocket() {
    Logger::socket("[UDP Socket] Instance for port " + std::to_string(port) +
                   " is being destroyed.");
    close();
}

void UdpSocket::init() {
    Logger::socket("[UDP Socket] Initializing socket on port: " +
                   std::to_string(port));

    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (udpSocket == FAILURE) {
        Logger::error("[UDP Socket] Failed to create socket.");
        throw std::runtime_error("Failed to create UDP socket.");
    }

    udpAddr.sin_family = AF_INET;
    udpAddr.sin_addr.s_addr = INADDR_ANY;
    udpAddr.sin_port = htons(port);

    if (bind(udpSocket, (struct sockaddr*)&udpAddr, sizeof(udpAddr)) <
        SUCCESS) {
        Logger::error("[UDP Socket] Failed to bind socket to port: " +
                      std::to_string(port));
        throw std::runtime_error("Bind failed for UDP socket on port " +
                                 std::to_string(port));
    }

    Logger::socket("[UDP Socket] Successfully bound to port: " +
                   std::to_string(port));
}

void UdpSocket::listen() {
    SmartBuffer smartBuffer;
    sockaddr_in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    Logger::socket("[UDP Socket] Listening for incoming messages on port: " +
                   std::to_string(port));

    while (true) {
        char rawBuffer[1024] = {0};
        int bytesRead = recvfrom(udpSocket, rawBuffer, sizeof(rawBuffer), 0,
                                 (struct sockaddr*)&clientAddr, &addrLen);

        if (bytesRead > 0) {
            Logger::packet("[UDP Socket] Received " +
                           std::to_string(bytesRead) + " bytes from " +
                           inet_ntoa(clientAddr.sin_addr) + ":" +
                           std::to_string(ntohs(clientAddr.sin_port)));

            smartBuffer.inject(reinterpret_cast<const uint8_t*>(rawBuffer),
                               bytesRead);
            smartBuffer.resetRead();

            Server::getProtocol().handleMessage(udpSocket, smartBuffer);
        } else {
            Logger::warning("[UDP Socket] Failed to receive data from client.");
        }
    }
}

void UdpSocket::close() {
    if (udpSocket != FAILURE) {
        ::close(udpSocket);
        Logger::socket("[UDP Socket] Socket on port " + std::to_string(port) +
                       " successfully closed.");
    } else {
        Logger::warning("[UDP Socket] Attempted to close an uninitialized or "
                        "already closed socket.");
    }
}
