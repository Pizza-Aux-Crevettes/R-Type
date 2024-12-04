/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.cpp
*/

#include "TcpSocket.hpp"
#include "Logger.hpp"
#include "Server.hpp"
#include <SmartBuffer.hpp>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

TcpSocket::TcpSocket(Config port) : port(port), tcpSocket(FAILURE) {}

TcpSocket::~TcpSocket() {
    close();
}

void TcpSocket::init() {
    tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcpSocket == FAILURE) {
        throw std::runtime_error("Failed to create TCP socket");
    }

    tcpAddr.sin_family = AF_INET;
    tcpAddr.sin_addr.s_addr = INADDR_ANY;
    tcpAddr.sin_port = htons(port);

    if (bind(tcpSocket, (struct sockaddr*)&tcpAddr, sizeof(tcpAddr)) <
        SUCCESS) {
        throw std::runtime_error("Bind failed for TCP socket");
    }

    if (::listen(tcpSocket, 3) < SUCCESS) {
        throw std::runtime_error("Listen failed for TCP socket");
    }

    Logger::info("TCP socket bound and listening on port " +
                 std::to_string(port));
}

void TcpSocket::listen() {
    Logger::info("Listening for TCP connections...");

    while (true) {
        int clientSocket = accept(tcpSocket, nullptr, nullptr);
        if (clientSocket < SUCCESS) {
            Logger::warning("Failed to accept TCP connection");
            continue;
        }

        Logger::info("New TCP client connected");

        clientThreads.emplace_back(
            [this, clientSocket]() { handleClient(clientSocket); });
    }
}

void TcpSocket::handleClient(int clientSocket) {
    SmartBuffer smartBuffer;

    while (true) {
        char rawBuffer[1024] = {0};

        int bytesRead = read(clientSocket, rawBuffer, sizeof(rawBuffer));
        if (bytesRead <= SUCCESS) {
            Logger::info("TCP client disconnected");
            ::close(clientSocket);
            break;
        }

        smartBuffer.inject(reinterpret_cast<const uint8_t*>(rawBuffer),
                           bytesRead);
        smartBuffer.resetRead();

        Server::getProtocol().handleMessage(clientSocket, smartBuffer);
    }
}

void TcpSocket::close() {
    if (tcpSocket != FAILURE) {
        ::close(tcpSocket);
        Logger::info("TCP socket closed.");
    }
}
