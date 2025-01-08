/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.cpp
*/

#include "socket/TcpSocket.hpp"
#include "protocol/Protocol.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"

std::vector<std::shared_ptr<Client>> TcpSocket::_clients;
std::mutex TcpSocket::_clientsMutex;

TcpSocket::TcpSocket() : _tcpSocket(FAILURE) {}

TcpSocket::~TcpSocket() {
    close();
}

void TcpSocket::init() {
    _tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_tcpSocket < SUCCESS) {
        throw std::runtime_error("Failed to create TCP socket.");
    }

    _tcpAddr.sin_family = AF_INET;
    _tcpAddr.sin_addr.s_addr = INADDR_ANY;
    _tcpAddr.sin_port = htons(PORT);

    if (bind(_tcpSocket, reinterpret_cast<sockaddr*>(&_tcpAddr),
             sizeof(_tcpAddr)) < 0) {
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

        int clientSocket = accept(
            _tcpSocket, reinterpret_cast<sockaddr*>(&clientAddr), &addrLen);
        if (clientSocket < SUCCESS) {
            Logger::warning("[TCP Socket] Accept failed.");
            continue;
        }

        sockaddr_in udpAddr{};

        auto client = std::make_shared<Client>(clientSocket, udpAddr);
        {
            std::lock_guard<std::mutex> lock(_clientsMutex);
            _clients.push_back(client);
        }

        Logger::socket("[TCP Socket] Client connected: " +
                       std::to_string(clientSocket));

        std::thread([this, client]() {
            SmartBuffer smartBuffer;

            this->handleRead(client, smartBuffer);
        }).detach();
    }
}

void TcpSocket::handleRead(std::shared_ptr<Client> client,
                           SmartBuffer& smartBuffer) const {
    while (true) {
        char buffer[1024] = {};
        ssize_t bytesRead =
            read(client->getTcpSocket(), buffer, sizeof(buffer));

        if (bytesRead <= 0) {
            Logger::socket("[TCP Socket] Client disconnected: " +
                           std::to_string(client->getTcpSocket()));

            ::close(client->getTcpSocket());
            removeClient(client);
            break;
        }

        smartBuffer.reset();
        smartBuffer.inject(reinterpret_cast<const uint8_t*>(buffer), bytesRead);

        Protocol::handleMessage(client, smartBuffer);
    }
}

void TcpSocket::addClient(std::shared_ptr<Client> client) const {
    std::lock_guard<std::mutex> lock(_clientsMutex);
    _clients.push_back(client);
}

void TcpSocket::removeClient(std::shared_ptr<Client> client) const {
    std::lock_guard<std::mutex> lock(_clientsMutex);
    _clients.erase(std::remove(_clients.begin(), _clients.end(), client),
                   _clients.end());
}

void TcpSocket::sendToOne(int clientSocket, const SmartBuffer& smartBuffer) {
    send(clientSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0);
}

void TcpSocket::sendToAll(const SmartBuffer& smartBuffer) {
    std::lock_guard<std::mutex> lock(_clientsMutex);

    for (auto& client : _clients) {
        int sock = client->getTcpSocket();

        if (sock >= SUCCESS) {
            send(sock, smartBuffer.getBuffer(), smartBuffer.getSize(), 0);
        }
    }
}

void TcpSocket::close() const {
    if (_tcpSocket >= SUCCESS) {
        ::close(_tcpSocket);

        Logger::socket("[TCP Socket] Closed.");
    }
}
