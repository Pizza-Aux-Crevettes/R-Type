/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** This file contains the implementation of the Socket class, managing socket creation, connection, and closure.
** Initializes server address and port, throws exception for invalid address.
** Uses Singleton for storing server address.
** Socket.cpp
*/

#include "network/socket/Socket.hpp"
#include <arpa/inet.h>
#include <stdexcept>
#include <unistd.h>
#include "network/socket/Singleton.hpp"
#include "util/Config.hpp"

Socket::Socket(const std::string& serverAddress, int port) : _socket(FAILURE) {
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, serverAddress.c_str(), &_serverAddr.sin_addr) <=
        SUCCESS) {
        throw std::runtime_error("Invalid server address");
    }
    Singleton::get().setSavedServerAddress(_serverAddr);
}

Socket::~Socket() {
    close();
}

void Socket::close() {
    if (_socket != FAILURE) {
        ::close(_socket);
        _socket = FAILURE;
    }
}