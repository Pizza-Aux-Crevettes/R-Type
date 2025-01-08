/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.cpp
*/

#include "socket/TcpSocket.hpp"
#include "socket/client/ClientManager.hpp"
#include "protocol/Protocol.hpp"
#include "util/Logger.hpp"

TcpSocket::TcpSocket() : _tcpSocket(FAILURE) {}

TcpSocket::~TcpSocket() {
    close();
}

void TcpSocket::init() {
    Logger::info("[TCP Socket] Initializing...");

    _tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_tcpSocket < SUCCESS) {
        throw std::runtime_error("Failed to create TCP socket.");
    }

    _tcpAddr.sin_family = AF_INET;
    _tcpAddr.sin_addr.s_addr = INADDR_ANY;
    _tcpAddr.sin_port = htons(PORT);

    if (bind(_tcpSocket, reinterpret_cast<sockaddr*>(&_tcpAddr), sizeof(_tcpAddr)) < 0) {
        throw std::runtime_error("Bind failed for TCP socket.");
    }

    if (listen(_tcpSocket, 3) < SUCCESS) {
        throw std::runtime_error("Listen failed for TCP socket.");
    }

    Logger::success("[TCP Socket] Successfully initialized on port " + std::to_string(PORT) + ".");
}

[[noreturn]] void TcpSocket::readLoop() const {
    Logger::info("[TCP Socket] Starting read loop...");

    while (true) {
        sockaddr_in clientAddr{};
        socklen_t addrLen = sizeof(clientAddr);

        int clientSocket = accept(_tcpSocket, reinterpret_cast<sockaddr*>(&clientAddr), &addrLen);
        if (clientSocket < SUCCESS) {
            Logger::warning("[TCP Socket] Accept failed.");
            continue;
        }

        sockaddr_in udpAddr{};
        
        auto client = ClientManager::getInstance().findOrCreateClient(clientAddr);
        client->setTcpSocket(clientSocket);

        Logger::info("[TCP Socket] Client connected. Socket: " +
                     std::to_string(clientSocket) + ", Address: " +
                     std::string(inet_ntoa(clientAddr.sin_addr)) + ":" +
                     std::to_string(ntohs(clientAddr.sin_port)));

        std::thread([this, client]() {
            SmartBuffer smartBuffer;
            this->handleRead(client, smartBuffer);
        }).detach();
    }
}

void TcpSocket::handleRead(std::shared_ptr<Client> client, SmartBuffer& smartBuffer) const {
    Logger::info("[TCP Socket] Listening to client: " + std::to_string(client->getTcpSocket()));

    while (true) {
        char buffer[1024] = {};
        ssize_t bytesRead = read(client->getTcpSocket(), buffer, sizeof(buffer));

        if (bytesRead <= 0) {
            Logger::info("[TCP Socket] Client disconnected: " + std::to_string(client->getTcpSocket()));

            ::close(client->getTcpSocket());
            ClientManager::getInstance().removeClient(client);
            break;
        }

        Logger::info("[TCP Socket] Received " + std::to_string(bytesRead) +
                     " bytes from client: " + std::to_string(client->getTcpSocket()));

        smartBuffer.reset();
        smartBuffer.inject(reinterpret_cast<const uint8_t*>(buffer), bytesRead);

        Protocol::handleMessage(client, smartBuffer);
    }
}

void TcpSocket::sendToOne(int clientSocket, const SmartBuffer& smartBuffer) {
    if (send(clientSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0) < 0) {
        Logger::error("[TCP Socket] Failed to send data.");
    }
}

void TcpSocket::sendToAll(const SmartBuffer& smartBuffer) {
    const auto& clients = ClientManager::getInstance().getAllClients();
    for (const auto& client : clients) {
        if (client->getTcpSocket() >= 0) {
            sendToOne(client->getTcpSocket(), smartBuffer);
        }
    }
}

void TcpSocket::close() const {
    if (_tcpSocket >= SUCCESS) {
        ::close(_tcpSocket);
        Logger::info("[TCP Socket] Socket closed.");
    }
}