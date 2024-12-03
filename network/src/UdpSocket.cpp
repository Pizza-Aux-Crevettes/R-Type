/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.cpp
*/

#include "UdpSocket.hpp"
#include "Logger.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

UdpSocket::UdpSocket(Config port) : port(port), udpSocket(FAILURE) {}

UdpSocket::~UdpSocket() {
    close();
}

void UdpSocket::init() {
    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpSocket == FAILURE) {
        throw std::runtime_error("Failed to create UDP socket");
    }

    udpAddr.sin_family = AF_INET;
    udpAddr.sin_addr.s_addr = INADDR_ANY;
    udpAddr.sin_port = htons(port);

    if (bind(udpSocket, (struct sockaddr*)&udpAddr, sizeof(udpAddr)) <
        SUCCESS) {
        throw std::runtime_error("Bind failed for UDP socket");
    }

    Logger::info("UDP socket bound to port " + std::to_string(port));
}

void UdpSocket::listen() {
    char buffer[1024] = {0};
    sockaddr_in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    Logger::info("Listening for UDP messages...");

    while (true) {
        int bytesRead = recvfrom(udpSocket, buffer, sizeof(buffer) - 1, 0,
                                 (struct sockaddr*)&clientAddr, &addrLen);
        if (bytesRead > 0) {
            buffer[bytesRead] = END_STR;
            Logger::info("UDP Received: " + std::string(buffer));
        }
    }
}

void UdpSocket::close() {
    if (udpSocket != FAILURE) {
        ::close(udpSocket);
        Logger::info("UDP socket closed.");
    }
}
