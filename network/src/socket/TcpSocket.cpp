/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.cpp
*/

#include "socket/TcpSocket.hpp"
#include "protocol/Protocol.hpp"
#include "socket/Server.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"
#include <SmartBuffer.hpp>
#include <arpa/inet.h>
#include <unistd.h>

TcpSocket::TcpSocket() : _tcpSocket(FAILURE) {}

TcpSocket::~TcpSocket() {
    close();
}

void TcpSocket::send(const int clientSocket, const SmartBuffer& smartBuffer) {
    ::send(clientSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0);
}

void TcpSocket::init() {
    _tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_tcpSocket == FAILURE) {
        throw std::runtime_error("Failed to create TCP socket.");
    }

    _tcpAddr.sin_family = AF_INET;
    _tcpAddr.sin_addr.s_addr = INADDR_ANY;
    _tcpAddr.sin_port = htons(PORT);

    if (bind(_tcpSocket, reinterpret_cast<sockaddr*>(&_tcpAddr),
             sizeof(_tcpAddr)) < SUCCESS) {
        throw std::runtime_error("Bind failed for TCP socket.");
    }
    if (listen(_tcpSocket, 3) < SUCCESS) {
        throw std::runtime_error("Listen failed for TCP socket.");
    }

    Logger::socket("[TCP Socket] Successfully initialized.");
}

[[noreturn]] void TcpSocket::readLoop() const {
    while (true) {
        sockaddr_in clientAddr{};
        socklen_t addrLen = sizeof(clientAddr);
        const int clientSocket = accept(
            _tcpSocket, reinterpret_cast<sockaddr*>(&clientAddr), &addrLen);

        if (clientSocket < SUCCESS) {
            Logger::warning("[TCP Socket] Accept failed.");
            continue;
        }
        handleClientRead(clientSocket);

        Logger::socket("[TCP Socket] Client connected: " +
                       std::to_string(clientSocket));
    }
}

void TcpSocket::handleClientRead(const int clientSocket) {
    SmartBuffer smartBuffer;

    while (true) {
        char buffer[1024] = {};
        const ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));

        if (bytesRead <= SUCCESS) {
            Logger::socket("[TCP Socket] Client disconnected: " +
                           std::to_string(clientSocket));

            ::close(clientSocket);
            break;
        }

        smartBuffer.inject(reinterpret_cast<const uint8_t*>(buffer), bytesRead);
        smartBuffer.resetRead();

        Protocol::handleMessage(clientSocket, smartBuffer);
    }
}

void TcpSocket::close() const {
    if (_tcpSocket != FAILURE) {
        ::close(_tcpSocket);

        Logger::socket("[TCP Socket] Closed.");
    }
}
