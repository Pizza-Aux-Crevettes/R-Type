/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.cpp
*/

#include "socket/UdpSocket.hpp"
#include "protocol/Protocol.hpp"
#include "socket/Singleton.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

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
    SmartBuffer smartBuffer;
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::DEFAULT);
    send(smartBuffer);
    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::NEW_PLAYER)
                << std::string{"Benjamin"};
    send(smartBuffer);
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
