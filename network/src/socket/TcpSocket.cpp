/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.cpp
*/

/**
 * @file TcpSocket.cpp
 * @brief Implementation of TcpSocket for handling TCP communication.
 */

#include "socket/TcpSocket.hpp"
#include "util/Logger.hpp"
#include "util/Singletons.hpp"
#include <SmartBuffer.hpp>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

TcpSocket::TcpSocket() : _tcpSocket(FAILURE) {
    Logger::socket("[TCP Socket] Instance created for port: " +
                   std::to_string(PORT));
}

TcpSocket::~TcpSocket() {
    Logger::socket("[TCP Socket] Instance for port " + std::to_string(PORT) +
                   " is being destroyed.");

    close();
}

void TcpSocket::sendTcp(int clientSocket, SmartBuffer& smartBuffer) {
    ssize_t bytesSent =
        send(clientSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0);

    if (bytesSent < 0) {
        Logger::error("[Socket] TCP send failed for clientSocket: " +
                      std::to_string(clientSocket));
    } else {
        Logger::info("[Socket] TCP send succeeded. Bytes sent: " +
                     std::to_string(bytesSent));
    }
}

void TcpSocket::init() {
    Logger::socket("[TCP Socket] Initializing socket on port: " +
                   std::to_string(PORT));

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
        Logger::error("[TCP Socket] Failed to bind socket to port: " +
                      std::to_string(PORT));

        throw std::runtime_error("Bind failed for TCP socket on port " +
                                 std::to_string(PORT));
    }

    if (::listen(_tcpSocket, 3) < SUCCESS) {
        Logger::error("[TCP Socket] Failed to listen on port: " +
                      std::to_string(PORT));

        throw std::runtime_error("Listen failed for TCP socket on port " +
                                 std::to_string(PORT));
    }

    Logger::socket("[TCP Socket] Successfully bound and listening on port: " +
                   std::to_string(PORT));
}

void TcpSocket::listen() {
    Logger::socket("[TCP Socket] Waiting for incoming connections on port: " +
                   std::to_string(PORT));

    while (true) {
        int clientSocket = accept(_tcpSocket, nullptr, nullptr);

        if (clientSocket < SUCCESS) {
            Logger::warning("[TCP Socket] Failed to accept a connection.");

            continue;
        }

        Logger::socket("[TCP Socket] New client connected. Client socket: " +
                       std::to_string(clientSocket));
        Logger::thread("[TCP Socket] Starting thread for client socket: " +
                       std::to_string(clientSocket));

        _clientThreads.emplace_back(
            [this, clientSocket]() { handleClient(clientSocket); });
    }
}

void TcpSocket::handleClient(int clientSocket) {
    SmartBuffer smartBuffer;

    Logger::thread("[TCP Socket] Handling client socket: " +
                   std::to_string(clientSocket));

    while (true) {
        char rawBuffer[1024] = {0};
        int bytesRead = read(clientSocket, rawBuffer, sizeof(rawBuffer));

        if (bytesRead <= SUCCESS) {
            Logger::socket("[TCP Socket] Client disconnected. Socket: " +
                           std::to_string(clientSocket));

            ::close(clientSocket);
            break;
        }

        Logger::packet(
            "[TCP Socket] Received " + std::to_string(bytesRead) +
            " bytes from client socket: " + std::to_string(clientSocket));

        smartBuffer.inject(reinterpret_cast<const uint8_t*>(rawBuffer),
                           bytesRead);
        smartBuffer.resetRead();

        Singletons::getProtocol().handleMessage(clientSocket, smartBuffer);
    }
}

void TcpSocket::close() {
    if (_tcpSocket != FAILURE) {
        ::close(_tcpSocket);

        Logger::socket("[TCP Socket] Socket on port " + std::to_string(PORT) +
                       " successfully closed.");
    } else {
        Logger::warning("[TCP Socket] Attempted to close an uninitialized or "
                        "already closed socket.");
    }
}
