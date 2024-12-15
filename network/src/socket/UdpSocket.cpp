/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.cpp
*/

#include "socket/UdpSocket.hpp"
#include "protocol/Protocol.hpp"
#include "socket/Server.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"
#include <SmartBuffer.hpp>
#include <arpa/inet.h>
#include <chrono>
#include <thread>
#include <unistd.h>

UdpSocket::UdpSocket() : _udpSocket(FAILURE) {}

UdpSocket::~UdpSocket() {
    close();
}

void UdpSocket::send(const int udpSocket, const sockaddr_in& clientAddr,
                     const SmartBuffer& smartBuffer) {
    sendto(udpSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0,
           reinterpret_cast<const sockaddr*>(&clientAddr), sizeof(clientAddr));
}

void UdpSocket::init() {
    _udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (_udpSocket == FAILURE) {
        throw std::runtime_error("Failed to create UDP socket.");
    }

    _udpAddr.sin_family = AF_INET;
    _udpAddr.sin_addr.s_addr = INADDR_ANY;
    _udpAddr.sin_port = htons(PORT);

    if (bind(_udpSocket, reinterpret_cast<sockaddr*>(&_udpAddr),
             sizeof(_udpAddr)) < SUCCESS) {
        throw std::runtime_error("Bind failed for UDP socket.");
    }

    Logger::socket("[UDP Socket] Successfully initialized.");
}

[[noreturn]] void UdpSocket::readLoop() {
    while (true) {
        handleRead();
    }
}

[[noreturn]] void UdpSocket::sendLoop() {
    while (true) {
        handleSend();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void UdpSocket::handleRead() {
    char buffer[1024] = {};
    sockaddr_in clientAddr{};
    socklen_t addrLen = sizeof(clientAddr);
    const ssize_t bytesRead =
        recvfrom(_udpSocket, buffer, sizeof(buffer), 0,
                 reinterpret_cast<sockaddr*>(&clientAddr), &addrLen);

    if (bytesRead > 0) {
        addClient(clientAddr);

        SmartBuffer smartBuffer;
        smartBuffer.inject(reinterpret_cast<const uint8_t*>(buffer), bytesRead);
        smartBuffer.resetRead();

        Protocol::handleMessage(_udpSocket, smartBuffer);
    }
}

void UdpSocket::handleSend() {
    SmartBuffer smartBuffer;
    smartBuffer << static_cast<int16_t>(0) << std::string("Test Message");

    const auto clients = getClients();

    if (clients.empty()) {
        return;
    }
    for (const auto& client : clients) {
        send(_udpSocket, client, smartBuffer);
    }
}

void UdpSocket::addClient(const sockaddr_in& clientAddr) {
    std::lock_guard lock(_clientsMutex);

    for (const auto& client : _clients) {
        if (client.sin_addr.s_addr == clientAddr.sin_addr.s_addr &&
            client.sin_port == clientAddr.sin_port) {
            return;
        }
    }

    _clients.push_back(clientAddr);

    Logger::info("[UDP Socket] New client registered: " +
                 std::string(inet_ntoa(clientAddr.sin_addr)) + ":" +
                 std::to_string(ntohs(clientAddr.sin_port)));
}

std::vector<sockaddr_in> UdpSocket::getClients() {
    std::lock_guard lock(_clientsMutex);
    return _clients;
}

void UdpSocket::close() const {
    if (_udpSocket != FAILURE) {
        ::close(_udpSocket);

        Logger::socket("[UDP Socket] Closed.");
    }
}
