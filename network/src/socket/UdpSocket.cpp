/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.cpp
*/

#include "socket/UdpSocket.hpp"
#include "component/player/PlayerManager.hpp"
#include "component/player/PlayerProtocol.hpp"
#include "socket/client/ClientManager.hpp"
#include "protocol/Protocol.hpp"
#include "util/Logger.hpp"

UdpSocket::UdpSocket() : _udpSocket(FAILURE) {}

UdpSocket::~UdpSocket() {
    close();
}

void UdpSocket::send(int udpSocket, const sockaddr_in& clientAddr,
                     const SmartBuffer& smartBuffer) {
    if (sendto(udpSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0,
               reinterpret_cast<const sockaddr*>(&clientAddr),
               sizeof(clientAddr)) < 0) {
        Logger::error("[UDP Socket] Failed to send data to: " +
                      std::string(inet_ntoa(clientAddr.sin_addr)) + ":" +
                      std::to_string(ntohs(clientAddr.sin_port)));
    } else {
        Logger::info("[UDP Socket] Data sent to: " +
                     std::string(inet_ntoa(clientAddr.sin_addr)) + ":" +
                     std::to_string(ntohs(clientAddr.sin_port)));
    }
}

void UdpSocket::init() {
    Logger::info("[UDP Socket] Initializing...");

    _udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (_udpSocket < SUCCESS) {
        throw std::runtime_error("Failed to create UDP socket.");
    }

    _udpAddr.sin_family = AF_INET;
    _udpAddr.sin_addr.s_addr = INADDR_ANY;
    _udpAddr.sin_port = htons(PORT);

    if (bind(_udpSocket, reinterpret_cast<sockaddr*>(&_udpAddr), sizeof(_udpAddr)) < 0) {
        throw std::runtime_error("Bind failed for UDP socket.");
    }

    Logger::success("[UDP Socket] Successfully initialized on port " + std::to_string(PORT) + ".");
}

[[noreturn]] void UdpSocket::readLoop() {
    Logger::info("[UDP Socket] Starting read loop...");

    SmartBuffer smartBuffer;

    while (true) {
        handleRead(smartBuffer);
    }
}

[[noreturn]] void UdpSocket::sendLoop() {
    Logger::info("[UDP Socket] Starting send loop...");

    SmartBuffer smartBuffer;

    while (true) {
        handleSend(smartBuffer);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void UdpSocket::handleRead(SmartBuffer& smartBuffer) {
    char buffer[1024] = {};
    sockaddr_in clientAddr{};
    socklen_t addrLen = sizeof(clientAddr);

    ssize_t bytesRead = recvfrom(_udpSocket, buffer, sizeof(buffer), 0,
                                 reinterpret_cast<sockaddr*>(&clientAddr), &addrLen);

    if (bytesRead > 0) {
        Logger::info("[UDP Socket] Received " + std::to_string(bytesRead) +
                     " bytes from: " + std::string(inet_ntoa(clientAddr.sin_addr)) +
                     ":" + std::to_string(ntohs(clientAddr.sin_port)));

        smartBuffer.reset();
        smartBuffer.inject(reinterpret_cast<const uint8_t*>(buffer), bytesRead);

        auto client = ClientManager::getInstance().findOrCreateClient(clientAddr);
        Protocol::handleMessage(client, smartBuffer);
    } else {
        Logger::warning("[UDP Socket] Failed to receive data.");
    }
}

void UdpSocket::handleSend(SmartBuffer& smartBuffer) {
    const auto& playersMap = PlayerManager::get().getPlayers();

    if (playersMap.empty()) {
        return;
    }

    std::vector<std::shared_ptr<Player>> players;
    players.reserve(playersMap.size());
    for (const auto& [playerId, player] : playersMap) {
        players.push_back(player);
    }

    for (const auto& player : players) {
        if (!player) {
            Logger::warning("[UDP Socket] Encountered a null player in the list. Skipping.");
            continue;
        }

        PlayerProtocol::sendPlayerPositionUpdate(_udpSocket, players, player, smartBuffer);
    }
}

void UdpSocket::close() const {
    if (_udpSocket >= SUCCESS) {
        ::close(_udpSocket);
        Logger::info("[UDP Socket] Closed.");
    }
}