/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Client.cpp
*/

#include "socket/client/Client.hpp"
#include "util/Logger.hpp"

Client::Client(int tcpSocket, const sockaddr_in& udpAddr)
    : _tcpSocket(tcpSocket), _udpAddr(udpAddr), _player(nullptr) {
    Logger::info("[Client] New client created. TCP Socket: " +
                 std::to_string(tcpSocket) +
                 ", UDP Address: " + std::string(inet_ntoa(udpAddr.sin_addr)) +
                 ":" + std::to_string(ntohs(udpAddr.sin_port)));
}

int Client::getTcpSocket() const {
    Logger::info("[Client] Retrieving TCP socket: " +
                 std::to_string(_tcpSocket));
    return _tcpSocket;
}

void Client::setTcpSocket(int socket) {
    Logger::info(
        "[Client] Setting TCP socket. Old: " + std::to_string(_tcpSocket) +
        ", New: " + std::to_string(socket));
    _tcpSocket = socket;
}

const sockaddr_in& Client::getUdpAddr() const {
    Logger::info("[Client] Retrieving UDP address: " +
                 std::string(inet_ntoa(_udpAddr.sin_addr)) + ":" +
                 std::to_string(ntohs(_udpAddr.sin_port)));
    return _udpAddr;
}

void Client::setUdpAddr(const sockaddr_in& addr) {
    Logger::info("[Client] Updating UDP address. Old: " +
                 std::string(inet_ntoa(_udpAddr.sin_addr)) + ":" +
                 std::to_string(ntohs(_udpAddr.sin_port)) +
                 ", New: " + std::string(inet_ntoa(addr.sin_addr)) + ":" +
                 std::to_string(ntohs(addr.sin_port)));
    _udpAddr = addr;
}

std::shared_ptr<Player> Client::getPlayer() const {
    if (_player) {
        Logger::info("[Client] Retrieving associated player. Player ID: " +
                     std::to_string(_player->getId()));
    } else {
        Logger::warning("[Client] No player associated with this client.");
    }
    return _player;
}

void Client::setPlayer(std::shared_ptr<Player> player) {
    if (player) {
        Logger::info("[Client] Associating player with ID: " +
                     std::to_string(player->getId()) + " to the client.");
    } else {
        Logger::info("[Client] Removing player association from the client.");
    }
    _player = std::move(player);
}

bool Client::hasSameUdpEndpoint(const sockaddr_in& other) const {
    bool isSame = (_udpAddr.sin_addr.s_addr == other.sin_addr.s_addr) &&
                  (_udpAddr.sin_port == other.sin_port);

    Logger::info("[Client] Comparing UDP endpoint. Current: " +
                 std::string(inet_ntoa(_udpAddr.sin_addr)) + ":" +
                 std::to_string(ntohs(_udpAddr.sin_port)) +
                 ", Other: " + std::string(inet_ntoa(other.sin_addr)) + ":" +
                 std::to_string(ntohs(other.sin_port)) +
                 ", Result: " + (isSame ? "Match" : "No Match"));

    return isSame;
}