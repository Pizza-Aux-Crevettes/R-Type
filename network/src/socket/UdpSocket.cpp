/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.cpp
*/

#include "socket/UdpSocket.hpp"
#include "component/map/MapProtocol.hpp"
#include "component/player/PlayerProtocol.hpp"
#include "component/room/RoomManager.hpp"
#include "protocol/Protocol.hpp"
#include "util/Logger.hpp"

std::vector<std::shared_ptr<Client>> UdpSocket::_clients;
std::mutex UdpSocket::_clientsMutex;

UdpSocket::UdpSocket() : _udpSocket(FAILURE) {}

UdpSocket::~UdpSocket() {
    close();
}

void UdpSocket::send(int udpSocket, const sockaddr_in& clientAddr,
                     const SmartBuffer& smartBuffer) {
    sendto(udpSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0,
           reinterpret_cast<const sockaddr*>(&clientAddr), sizeof(clientAddr));
}

void UdpSocket::init() {
    _udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (_udpSocket < SUCCESS) {
        throw std::runtime_error("Failed to create UDP socket.");
    }

    _udpAddr.sin_family = AF_INET;
    _udpAddr.sin_addr.s_addr = INADDR_ANY;
    _udpAddr.sin_port = htons(PORT);

    if (bind(_udpSocket, reinterpret_cast<sockaddr*>(&_udpAddr),
             sizeof(_udpAddr)) < 0) {
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
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void UdpSocket::handleRead(SmartBuffer& smartBuffer) {
    char buffer[1024] = {};
    sockaddr_in clientAddr{};
    socklen_t addrLen = sizeof(clientAddr);
    ssize_t bytesRead =
        recvfrom(_udpSocket, buffer, sizeof(buffer), 0,
                 reinterpret_cast<sockaddr*>(&clientAddr), &addrLen);

    if (bytesRead > 0) {
        smartBuffer.reset();
        smartBuffer.inject(reinterpret_cast<const uint8_t*>(buffer), bytesRead);

        auto client = findOrCreateClient(clientAddr);

        Protocol::handleMessage(client, smartBuffer);
    }
}

void UdpSocket::handleSend(SmartBuffer& smartBuffer) {
    const auto& rooms = RoomManager::get().getRooms();
    if (rooms.empty()) {
        return;
    }

    for (const auto& room : rooms) {
        if (!room->isGameStarted()) {
            continue;
        }

        auto map = room->getMap();
        if (!map) {
            Logger::warning("[UdpSocket] Room " + room->getCode() +
                            " has no map assigned.");
            continue;
        }

        map->incrementViewport();

        const auto& players = room->getPlayers();
        for (const auto& player : players) {
            PlayerProtocol::sendPlayerPositionUpdate(_udpSocket, players,
                                                     player, smartBuffer);
            MapProtocol::sendViewportUpdate(_udpSocket,
                                            player->getClientAddress(),
                                            map->getViewport(), smartBuffer);
            MapProtocol::sendObstaclesUpdate(_udpSocket,
                                             player->getClientAddress(),
                                             map->getObstacles(), smartBuffer);
        }
    }
}

std::shared_ptr<Client> UdpSocket::findOrCreateClient(const sockaddr_in& addr) {
    std::lock_guard<std::mutex> lock(_clientsMutex);

    for (auto& client : _clients) {
        if (client->hasSameUdpEndpoint(addr)) {
            return client;
        }
    }

    auto newClient = std::make_shared<Client>(-1, addr);

    _clients.push_back(newClient);

    Logger::info("[UDP Socket] New client discovered via UDP: " +
                 std::string(inet_ntoa(addr.sin_addr)) + ":" +
                 std::to_string(ntohs(addr.sin_port)));

    return newClient;
}

void UdpSocket::close() const {
    if (_udpSocket >= SUCCESS) {
        ::close(_udpSocket);

        Logger::socket("[UDP Socket] Closed.");
    }
}
