/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.cpp
*/

#include "socket/UdpSocket.hpp"
#include "util/Logger.hpp"
#include "util/Singletons.hpp"
#include <SmartBuffer.hpp>
#include <arpa/inet.h>
#include <chrono>
#include <cstring>
#include <thread>
#include <unistd.h>

UdpSocket::UdpSocket() : _udpSocket(FAILURE) {
    Logger::socket("[UDP Socket] Instance created.");
}

UdpSocket::~UdpSocket() {
    close();
}

void UdpSocket::send(int udpSocket, const sockaddr_in& clientAddr,
                     SmartBuffer& smartBuffer) {
    ssize_t bytesSent =
        sendto(udpSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0,
               (struct sockaddr*)&clientAddr, sizeof(clientAddr));

    if (bytesSent < 0) {
        Logger::error("[UDP Socket] Send failed.");
    } else {
        Logger::info("[UDP Socket] Sent " + std::to_string(bytesSent) +
                     " bytes to client.");
    }
}

void UdpSocket::init() {
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
        Logger::error("[UDP Socket] Failed to bind socket.");

        throw std::runtime_error("Bind failed for UDP socket.");
    }

    Logger::socket("[UDP Socket] Successfully initialized.");
}

void UdpSocket::readLoop() {
    while (true) {
        handleRead();
    }
}

void UdpSocket::sendLoop() {
    while (true) {
        handleSend();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void UdpSocket::handleRead() {
    char buffer[1024] = {0};
    sockaddr_in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    int bytesRead = recvfrom(_udpSocket, buffer, sizeof(buffer), 0,
                             (struct sockaddr*)&clientAddr, &addrLen);

    if (bytesRead > 0) {
        SmartBuffer smartBuffer;
        smartBuffer.inject(reinterpret_cast<const uint8_t*>(buffer), bytesRead);
        smartBuffer.resetRead();

        Singletons::getProtocol().handleMessage(_udpSocket, smartBuffer);
    }
}

void UdpSocket::handleSend() {
    Logger::info("[UDP Socket] Sending data...");
}

void UdpSocket::close() {
    if (_udpSocket != FAILURE) {
        ::close(_udpSocket);

        Logger::socket("[UDP Socket] Closed.");
    }
}
