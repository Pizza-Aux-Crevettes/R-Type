/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.cpp
*/

#include "socket/TcpSocket.hpp"
#include "util/Config.hpp"
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

TcpSocket::TcpSocket(const std::string& serverAddress, int port)
    : Socket(serverAddress, port) {}

TcpSocket::~TcpSocket() {
    closeSocket();
}

void TcpSocket::init() {
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == FAILURE) {
        throw std::runtime_error("Failed to create TCP socket");
    }
}

void TcpSocket::connectSocket() {
    if (connect(_socket, reinterpret_cast<sockaddr*>(&_serverAddr),
                sizeof(_serverAddr)) < SUCCESS) {
        throw std::runtime_error("Failed to connect to TCP server");
    }
}

void TcpSocket::sendBuffer(const SmartBuffer& smartBuffer) {
    if (send(_socket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0) <
        SUCCESS) {
        throw std::runtime_error("Failed to send TCP message");
    }
}

SmartBuffer TcpSocket::receiveBuffer() {
    SmartBuffer smartBuffer;
    char buffer[1024];
    ssize_t bytesReceived = recv(_socket, buffer, sizeof(buffer), 0);

    if (bytesReceived <= SUCCESS) {
        throw std::runtime_error("Failed to receive TCP message");
    }
    smartBuffer.inject(reinterpret_cast<uint8_t*>(buffer), bytesReceived);
    return smartBuffer;
}
