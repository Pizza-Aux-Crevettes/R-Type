/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.cpp
*/

#include "socket/TcpSocket.hpp"
#include "util/Logger.hpp"
#include "util/Singletons.hpp"
#include <SmartBuffer.hpp>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

TcpSocket::TcpSocket() : _tcpSocket(FAILURE) {
    Logger::socket("[TCP Socket] Instance created.");
}

TcpSocket::~TcpSocket() {
    close();
}

void TcpSocket::send(int clientSocket, SmartBuffer& smartBuffer) {
    ssize_t bytesSent =
        ::send(clientSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0);

    if (bytesSent < 0) {
        Logger::error("[TCP Socket] Send failed.");
    } else {
        Logger::info("[TCP Socket] Sent " + std::to_string(bytesSent) +
                     " bytes to client.");
    }
}

void TcpSocket::init() {
    _tcpSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (_tcpSocket == FAILURE) {
        Logger::error("[TCP Socket] Failed to create socket.");

        throw std::runtime_error("Failed to create TCP socket.");
    }

    _tcpAddr.sin_family = AF_INET;
    _tcpAddr.sin_addr.s_addr = INADDR_ANY;
    _tcpAddr.sin_port = htons(PORT);

    if (bind(_tcpSocket, (struct sockaddr*)&_tcpAddr, sizeof(_tcpAddr)) <
        SUCCESS) {
        Logger::error("[TCP Socket] Failed to bind socket.");

        throw std::runtime_error("Bind failed for TCP socket.");
    }

    if (listen(_tcpSocket, 3) < SUCCESS) {
        Logger::error("[TCP Socket] Failed to listen.");

        throw std::runtime_error("Listen failed for TCP socket.");
    }

    Logger::socket("[TCP Socket] Successfully initialized.");
}

void TcpSocket::readLoop() {
    while (true) {
        int clientSocket = accept(_tcpSocket, nullptr, nullptr);

        if (clientSocket < SUCCESS) {
            Logger::warning("[TCP Socket] Accept failed.");
            continue;
        }

        Logger::socket("[TCP Socket] Client connected: " +
                       std::to_string(clientSocket));

        handleClientRead(clientSocket);
    }
}

void TcpSocket::handleClientRead(int clientSocket) {
    SmartBuffer smartBuffer;

    while (true) {
        char buffer[1024] = {0};
        int bytesRead = read(clientSocket, buffer, sizeof(buffer));

        if (bytesRead <= SUCCESS) {
            Logger::socket("[TCP Socket] Client disconnected: " +
                           std::to_string(clientSocket));

            ::close(clientSocket);
            break;
        }

        smartBuffer.inject(reinterpret_cast<const uint8_t*>(buffer), bytesRead);
        smartBuffer.resetRead();

        Singletons::getProtocol().handleMessage(clientSocket, smartBuffer);
    }
}

void TcpSocket::close() {
    if (_tcpSocket != FAILURE) {
        ::close(_tcpSocket);

        Logger::socket("[TCP Socket] Closed.");
    }
}
