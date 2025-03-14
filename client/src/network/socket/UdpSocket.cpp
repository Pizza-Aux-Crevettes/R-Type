/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** This file contains the implementation of the UdpSocket class for managing UDP socket initialization, sending,
** and receiving messages. Inherits from Socket and uses Singleton 
** for storing socket and server information.
** UdpSocket.cpp
*/

#include "network/socket/UdpSocket.hpp"
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>
#include "network/protocol/Protocol.hpp"
#include "network/socket/Singleton.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"

UdpSocket::UdpSocket(const std::string& serverAddress, int port)
    : Socket(serverAddress, port) {}

UdpSocket::~UdpSocket() {
    close();
}

void UdpSocket::init() {
    _socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (_socket == FAILURE) {
        throw std::runtime_error("Failed to create UDP socket");
    }
    Singleton::get().setSavedUdpSocket(_socket);
}

void UdpSocket::send(const SmartBuffer& smartBuffer) {
    const auto& serverAddress = Singleton::get().getSavedServerAddress();
    if (sendto(Singleton::get().getSavedUdpSocket(), smartBuffer.getBuffer(),
               smartBuffer.getSize(), 0,
               reinterpret_cast<const sockaddr*>(&serverAddress),
               sizeof(serverAddress)) < SUCCESS) {
        throw std::runtime_error("Failed to send UDP message");
    }
}

SmartBuffer UdpSocket::receive() {
    SmartBuffer smartBuffer;
    char buffer[1024];
    socklen_t serverLen = sizeof(_serverAddr);
    const ssize_t bytesReceived =
        recvfrom(_socket, buffer, sizeof(buffer), 0,
                 reinterpret_cast<sockaddr*>(&_serverAddr), &serverLen);

    if (bytesReceived <= SUCCESS) {
        throw std::runtime_error("Failed to receive UDP message");
    }
    smartBuffer.inject(reinterpret_cast<uint8_t*>(buffer), bytesReceived);
    return smartBuffer;
}