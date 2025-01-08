/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Client.cpp
*/

#include "socket/Client.hpp"

Client::Client(int tcpSocket, const sockaddr_in& udpAddr)
    : _tcpSocket(tcpSocket), _udpAddr(udpAddr), _player(nullptr) {}

int Client::getTcpSocket() const {
    return _tcpSocket;
}

void Client::setTcpSocket(int socket) {
    _tcpSocket = socket;
}

const sockaddr_in& Client::getUdpAddr() const {
    return _udpAddr;
}

void Client::setUdpAddr(const sockaddr_in& addr) {
    _udpAddr = addr;
}

std::shared_ptr<Player> Client::getPlayer() const {
    return _player;
}

void Client::setPlayer(std::shared_ptr<Player> player) {
    _player = std::move(player);
}

bool Client::hasSameUdpEndpoint(const sockaddr_in& other) const {
    return (_udpAddr.sin_addr.s_addr == other.sin_addr.s_addr) &&
           (_udpAddr.sin_port == other.sin_port);
}