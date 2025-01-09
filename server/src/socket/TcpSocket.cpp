/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.cpp
*/

#include "socket/TcpSocket.hpp"
#include <SmartBuffer.hpp>
#include <arpa/inet.h>
#include <thread>
#include <unistd.h>
#include "protocol/Protocol.hpp"
#include "socket/Server.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"

std::vector<int> TcpSocket::_clients;
std::mutex TcpSocket::_clientsMutex;

TcpSocket::TcpSocket() : _tcpSocket(FAILURE) {}

TcpSocket::~TcpSocket() {
    close();
}

void TcpSocket::sendToOne(const int clientSocket,
                          const SmartBuffer& smartBuffer) {
    send(clientSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0);
}

void TcpSocket::sendToAll(const SmartBuffer& smartBuffer) {
    std::lock_guard lock(_clientsMutex);

    for (const int clientSocket : _clients) {
        send(clientSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0);
    }
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

        addClient(clientSocket);

        Logger::socket("[TCP Socket] Client connected: " +
                       std::to_string(clientSocket));

        std::thread([this, clientSocket, clientAddr]() {
            SmartBuffer smartBuffer;

            this->handleRead(clientSocket, smartBuffer, clientAddr);
        }).detach();
    }
}

void TcpSocket::handleRead(const int clientSocket, SmartBuffer& smartBuffer,
                           const sockaddr_in& clientAddr) {

    while (true) {
        char buffer[1024] = {};
        const ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));

        if (bytesRead <= SUCCESS) {
            Logger::socket("[TCP Socket] Client disconnected: " +
                           std::to_string(clientSocket));

            ::close(clientSocket);
            removeClient(clientSocket);
            break;
        }

        smartBuffer.reset();
        smartBuffer.inject(reinterpret_cast<const uint8_t*>(buffer), bytesRead);

        Protocol::handleMessage(clientSocket, smartBuffer, clientAddr);
    }
}

void TcpSocket::addClient(const int clientSocket) {
    std::lock_guard lock(_clientsMutex);
    _clients.push_back(clientSocket);
}

void TcpSocket::removeClient(const int clientSocket) {
    std::lock_guard lock(_clientsMutex);
    std::erase(_clients, clientSocket);
}

std::vector<int> TcpSocket::getClients() {
    std::lock_guard lock(_clientsMutex);
    return _clients;
}

void TcpSocket::close() const {
    if (_tcpSocket != FAILURE) {
        ::close(_tcpSocket);

        Logger::socket("[TCP Socket] Closed.");
    }
}