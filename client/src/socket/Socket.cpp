/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Socket.cpp
*/

#include "socket/Socket.hpp"
#include "util/Config.hpp"
#include <arpa/inet.h>
#include <stdexcept>
#include <unistd.h>

Socket::Socket(const std::string& serverAddress, int port) : _socket(FAILURE) {
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, serverAddress.c_str(), &_serverAddr.sin_addr) <=
        SUCCESS) {
        throw std::runtime_error("Invalid server address");
    }
}

Socket::~Socket() {
    closeSocket();
}

void Socket::closeSocket() {
    if (_socket != FAILURE) {
        close(_socket);
        _socket = FAILURE;
    }
}