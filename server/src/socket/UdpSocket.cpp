/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.cpp
*/

#include "socket/UdpSocket.hpp"
#include <SmartBuffer.hpp>
#include <arpa/inet.h>
#include <chrono>
#include <thread>
#include <unistd.h>
#include "component/map/MapProtocol.hpp"
#include "component/player/PlayerManager.hpp"
#include "component/player/PlayerProtocol.hpp"
#include "protocol/Protocol.hpp"
#include "socket/Server.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"

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
    SmartBuffer smartBuffer;

    while (true) {
        handleRead(smartBuffer);
    }
}

[[noreturn]] void UdpSocket::sendLoop() {
    SmartBuffer smartBuffer;

    while (true) {
        handleSend(smartBuffer);
        std::this_thread::sleep_for(std::chrono::milliseconds(FREQUENCY));
    }
}

void UdpSocket::handleRead(SmartBuffer& smartBuffer) {
    char buffer[1024] = {};
    sockaddr_in clientAddr{};
    socklen_t addrLen = sizeof(clientAddr);
    const ssize_t bytesRead =
        recvfrom(_udpSocket, buffer, sizeof(buffer), 0,
                 reinterpret_cast<sockaddr*>(&clientAddr), &addrLen);

    if (bytesRead > 0) {
        addClient(clientAddr);

        smartBuffer.reset();
        smartBuffer.inject(reinterpret_cast<const uint8_t*>(buffer), bytesRead);

        Protocol::handleMessage(_udpSocket, smartBuffer, clientAddr);
    }
}

void UdpSocket::handleSend(SmartBuffer& smartBuffer) {
    const auto clients = getClients();
    const auto& players = PlayerManager::get().getPlayers();

    if (clients.empty() || players.empty()) {
        return;
    }

    for (const sockaddr_in& client : clients) {
        for (const auto& [playerId, player] : players) {
            PlayerProtocol::sendPositionsUpdate(_udpSocket, client, player,
                                                smartBuffer);
        }

        MapProtocol::sendViewportUpdate(_udpSocket, client, smartBuffer);
        MapProtocol::sendObstaclesUpdate(_udpSocket, client, smartBuffer);
    }

    MapManager::get().getCurrentMap()->incrementViewport();
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
