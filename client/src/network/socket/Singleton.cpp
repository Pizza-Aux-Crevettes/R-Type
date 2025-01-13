/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Singleton.hpp
*/

#include "network/socket/Singleton.hpp"
#include <mutex>

std::mutex Singleton::_mutex;

Singleton::Singleton()
    : _savedTcpSocket(-1), _savedUdpSocket(-1), _savedServerAddress{} {}

Singleton::~Singleton() = default;

Singleton& Singleton::get() {
    static Singleton instance;
    return instance;
}

void Singleton::setSavedTcpSocket(int tcpSocket) {
    std::lock_guard<std::mutex> lock(_mutex);
    _savedTcpSocket = tcpSocket;
}

int Singleton::getSavedTcpSocket() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _savedTcpSocket;
}

void Singleton::setSavedUdpSocket(int udpSocket) {
    std::lock_guard<std::mutex> lock(_mutex);
    _savedUdpSocket = udpSocket;
}

int Singleton::getSavedUdpSocket() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _savedUdpSocket;
}

void Singleton::setSavedServerAddress(const sockaddr_in& serverAddress) {
    std::lock_guard<std::mutex> lock(_mutex);
    _savedServerAddress = serverAddress;
}

sockaddr_in Singleton::getSavedServerAddress() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _savedServerAddress;
}
