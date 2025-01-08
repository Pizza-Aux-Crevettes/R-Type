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
    Logger::info("[TCP Socket] Initializing...");

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

    Logger::success("[TCP Socket] Successfully initialized on port " +
                    std::to_string(PORT) + ".");
}

[[noreturn]] void TcpSocket::readLoop() const {
    Logger::info("[TCP Socket] Starting read loop...");

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

        addClient(client);

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

void TcpSocket::handleRead(std::shared_ptr<Client> client,
                           SmartBuffer& smartBuffer) const {
    Logger::info("[TCP Socket] Listening to client: " +
                 std::to_string(client->getTcpSocket()));

    while (true) {
        char buffer[1024] = {};
        ssize_t bytesRead =
            read(client->getTcpSocket(), buffer, sizeof(buffer));

        if (bytesRead <= 0) {
            Logger::info("[TCP Socket] Client disconnected: " +
                         std::to_string(client->getTcpSocket()));

            ::close(client->getTcpSocket());
            removeClient(client);
            break;
        }

        Logger::info(
            "[TCP Socket] Received " + std::to_string(bytesRead) +
            " bytes from client: " + std::to_string(client->getTcpSocket()));

        smartBuffer.reset();
        smartBuffer.inject(reinterpret_cast<const uint8_t*>(buffer), bytesRead);

        Protocol::handleMessage(client, smartBuffer);
    }
}

void TcpSocket::addClient(std::shared_ptr<Client> client) const {
    std::lock_guard<std::mutex> lock(_clientsMutex);
    _clients.push_back(client);

    Logger::info("[TCP Socket] Client added. Total clients: " +
                 std::to_string(_clients.size()));
}

void TcpSocket::removeClient(std::shared_ptr<Client> client) const {
    std::lock_guard<std::mutex> lock(_clientsMutex);

    _clients.erase(std::remove(_clients.begin(), _clients.end(), client),
                   _clients.end());

    Logger::info("[TCP Socket] Client removed. Total clients: " +
                 std::to_string(_clients.size()));
}

void TcpSocket::sendToOne(int clientSocket, const SmartBuffer& smartBuffer) {
    Logger::info("[TCP Socket] Sending data to client socket: " +
                 std::to_string(clientSocket));

    if (send(clientSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0) <
        0) {
        Logger::error("[TCP Socket] Failed to send data to client: " +
                      std::to_string(clientSocket));
    }
}

void TcpSocket::sendToAll(const SmartBuffer& smartBuffer) {
    std::lock_guard<std::mutex> lock(_clientsMutex);

    Logger::info("[TCP Socket] Broadcasting data to all clients. Total: " +
                 std::to_string(_clients.size()));

    for (auto& client : _clients) {
        int sock = client->getTcpSocket();
        if (sock >= SUCCESS) {
            if (send(sock, smartBuffer.getBuffer(), smartBuffer.getSize(), 0) <
                0) {
                Logger::error("[TCP Socket] Failed to send data to client: " +
                              std::to_string(sock));
            }
        }
    }
}

void TcpSocket::close() const {
    if (_tcpSocket >= SUCCESS) {
        ::close(_tcpSocket);
        Logger::info("[TCP Socket] Socket closed.");
    }
}