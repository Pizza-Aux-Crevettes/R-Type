/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.cpp
*/

#include "socket/UdpSocket.hpp"
#include "util/Config.hpp"
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

UdpSocket::UdpSocket(const std::string& serverAddress, int port)
    : Socket(serverAddress, port) {}

UdpSocket::~UdpSocket() {
    closeSocket();
}

void UdpSocket::init() {
    _socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (_socket == FAILURE) {
        throw std::runtime_error("Failed to create UDP socket");
    }
}

void UdpSocket::sendBuffer(const SmartBuffer& smartBuffer) {
    if (sendto(_socket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0,
               reinterpret_cast<sockaddr*>(&_serverAddr),
               sizeof(_serverAddr)) < SUCCESS) {
        throw std::runtime_error("Failed to send UDP message");
    }
}

SmartBuffer UdpSocket::receiveBuffer() {
    SmartBuffer smartBuffer;
    char buffer[1024];
    socklen_t serverLen = sizeof(_serverAddr);
    ssize_t bytesReceived =
        recvfrom(_socket, buffer, sizeof(buffer), 0,
                 reinterpret_cast<sockaddr*>(&_serverAddr), &serverLen);

    if (bytesReceived <= SUCCESS) {
        throw std::runtime_error("Failed to receive UDP message");
    }
    smartBuffer.inject(reinterpret_cast<uint8_t*>(buffer), bytesReceived);
    return smartBuffer;
}
