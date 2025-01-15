/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.cpp
*/

#include "socket/TcpSocket.hpp"
#include "component/player/PlayerManager.hpp"
#include "protocol/Protocol.hpp"
#include "socket/Server.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"

/**
 * @brief Get the TcpSocket instance
 *
 * @return TcpSocket&
 */
TcpSocket& TcpSocket::get() {
    static TcpSocket instance;
    return instance;
}

/**
 * @brief Destroy the TcpSocket:: TcpSocket object
 *
 */
TcpSocket::~TcpSocket() {
    close();
}

/**
 * @brief Initialize the TCP socket
 *
 */
void TcpSocket::init() {
    _tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_tcpSocket == FAILURE) {
        throw std::runtime_error("Failed to create TCP socket.");
    }

    int opt = 1;
    if (setsockopt(_tcpSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) <
        0) {
        throw std::runtime_error(
            "[TCP Socket] Failed to set socket options (SO_REUSEADDR).");
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

/**
 * @brief Read loop for the TCP socket
 *
 */
void TcpSocket::readLoop() const {
    while (true) {
        sockaddr_in clientAddr{};
        socklen_t addrLen = sizeof(clientAddr);

        const int clientSocket = accept(
            _tcpSocket, reinterpret_cast<sockaddr*>(&clientAddr), &addrLen);
        if (clientSocket < SUCCESS) {
            Logger::warning("[TCP Socket] Accept failed.");
            continue;
        }

        TcpSocket::get().addClient(clientSocket);

        Logger::socket("[TCP Socket] New client connected: " +
                       std::to_string(clientSocket));

        std::thread([clientSocket, clientAddr]() {
            SmartBuffer smartBuffer;
            TcpSocket::get().handleRead(clientSocket, smartBuffer);
        }).detach();
    }
}

/**
 * @brief Handle the read event
 *
 * @param clientSocket The client socket
 * @param smartBuffer The SmartBuffer to use for the response
 */
void TcpSocket::handleRead(const int clientSocket, SmartBuffer& smartBuffer) {
    while (true) {
        char buffer[DEFAULT_BYTES] = {};

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

        Protocol::handleMessage(clientSocket, smartBuffer);
    }
}

/**
 * @brief Send a message to a specific client
 *
 * @param clientSocket The client socket
 * @param smartBuffer The message to send
 */
void TcpSocket::sendToOne(const int clientSocket,
                          const SmartBuffer& smartBuffer) {
    send(clientSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0);
}

/**
 * @brief Send a message to all clients
 *
 * @param smartBuffer The message to send
 */
void TcpSocket::sendToAll(const SmartBuffer& smartBuffer) {
    std::lock_guard lock(_clientsMutex);
    for (const int clientSocket : _clients) {
        send(clientSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0);
    }
}

/**
 * @brief Add a client to the list
 *
 * @param clientSocket The client socket
 */
void TcpSocket::addClient(const int clientSocket) {
    std::lock_guard lock(_clientsMutex);
    _clients.push_back(clientSocket);
}

/**
 * @brief Remove a client from the list
 *
 * @param clientSocket The client socket
 */
void TcpSocket::removeClient(const int clientSocket) {
    std::lock_guard lock(_clientsMutex);
    _clients.erase(std::remove(_clients.begin(), _clients.end(), clientSocket),
                   _clients.end());

    for (auto& [id, player] : PlayerManager::get().getPlayers()) {
        if (player->getClientSocket() == clientSocket) {
            PlayerManager::get().removePlayer(id);

            Logger::success("[TcpSocket] Removed player with ID: " + std::to_string(id) +
                         ", associated with client socket " +
                         std::to_string(clientSocket));
            break;
        }
    }
}

/**
 * @brief Get all clients
 *
 * @return std::vector<int>
 */
std::vector<int> TcpSocket::getClients() {
    std::lock_guard lock(_clientsMutex);
    return _clients;
}

/**
 * @brief Close the TCP socket
 *
 */
void TcpSocket::close() const {
    if (_tcpSocket != FAILURE) {
        ::close(_tcpSocket);

        Logger::socket("[TCP Socket] Closed.");
    }
}
