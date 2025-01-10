/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.cpp
*/

#include "network/socket/TcpSocket.hpp"
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>
#include "network/protocol/Protocol.hpp"
#include "network/socket/Singleton.hpp"
#include "util/Config.hpp"

TcpSocket::TcpSocket(const std::string& serverAddress, const int port)
    : Socket(serverAddress, port) {}

TcpSocket::~TcpSocket() {
    close();
}

void TcpSocket::init() {
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == FAILURE) {
        throw std::runtime_error("Failed to create TCP socket");
    }
    Singleton::get().setSavedTcpSocket(_socket);
}

void TcpSocket::connect() {
    if (::connect(_socket, reinterpret_cast<sockaddr*>(&_serverAddr),
                  sizeof(_serverAddr)) < SUCCESS) {
        throw std::runtime_error("Failed to connect to TCP server");
    }
}

void TcpSocket::send(const SmartBuffer& smartBuffer) {
    if (::send(Singleton::get().getSavedTcpSocket(), smartBuffer.getBuffer(),
               smartBuffer.getSize(), 0) < SUCCESS) {
        throw std::runtime_error("Failed to send TCP message");
    }
}

SmartBuffer TcpSocket::receive() const {
    SmartBuffer smartBuffer;
    char buffer[1024];
    const ssize_t bytesReceived = recv(_socket, buffer, sizeof(buffer), 0);
    if (bytesReceived <= SUCCESS) {
        throw std::runtime_error("Failed to receive TCP message");
    }
    smartBuffer.inject(reinterpret_cast<uint8_t*>(buffer), bytesReceived);
    return smartBuffer;
}
