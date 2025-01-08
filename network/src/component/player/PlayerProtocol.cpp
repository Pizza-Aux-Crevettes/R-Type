/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerProtocol.cpp
*/

#include "component/player/PlayerProtocol.hpp"
#include "component/player/PlayerManager.hpp"
#include "socket/client/ClientManager.hpp"
#include "protocol/Protocol.hpp"
#include "socket/TcpSocket.hpp"
#include "socket/UdpSocket.hpp"
#include "util/Logger.hpp"

void PlayerProtocol::newPlayer(std::shared_ptr<Client> client,
                               SmartBuffer& smartBuffer) {
    Logger::info("[PlayerProtocol] Handling new player creation.");

    std::string name;
    smartBuffer >> name;

    Logger::info("[PlayerProtocol] Received new player name: " + name);

    auto player = PlayerManager::get().createPlayer(name);
    if (!player) {
        Logger::error("[PlayerProtocol] Failed to create player with name: " +
                      name);
        return;
    }

    client->setPlayer(player);

    Logger::info("[PlayerProtocol] Player created successfully. Player ID: " +
                 std::to_string(player->getId()));

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::NEW_PLAYER_CALLBACK)
                << player->getId();

    TcpSocket::sendToOne(client->getTcpSocket(), smartBuffer);

    Logger::info("[PlayerProtocol] NEW_PLAYER_CALLBACK sent to client.");

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::NEW_PLAYER_BROADCAST)
                << player->getId() << name;

    TcpSocket::sendToAll(smartBuffer);

    Logger::info("[PlayerProtocol] NEW_PLAYER_BROADCAST sent to all clients.");
}

void PlayerProtocol::sendPlayerPositionUpdate(
    int udpSocket,
    const std::vector<std::shared_ptr<Player>> &players,
    const std::shared_ptr<Player> &player,
    SmartBuffer &smartBuffer)
{
    if (!player) {
        return;
    }

    const auto &pos = player->getPosition();
    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::PLAYER_UPDATE_POSITION)
                << player->getId()
                << pos.getX()
                << pos.getY();

    auto allClients = ClientManager::getInstance().getAllClients();
    for (auto &c : allClients) {
        const sockaddr_in &udpAddr = c->getUdpAddr();
        if (udpAddr.sin_addr.s_addr == 0 || udpAddr.sin_port == 0) {
            Logger::warning("[PlayerProtocol] Client has invalid UDP address (0.0.0.0:0). Skipping.");
            continue;
        }
        UdpSocket::send(udpSocket, udpAddr, smartBuffer);

        if (c->getPlayer()) {
            Logger::info("[PlayerProtocol] Sent position update to Player ID: " +
                         std::to_string(c->getPlayer()->getId()) + " for Player ID: " +
                         std::to_string(player->getId()) + "X: " + std::to_string(pos.getX()) + "Y: " + std::to_string(pos.getY()) + ".");
        } else {
            Logger::info("[PlayerProtocol] Sent position update to a client with no attached player, " 
                         "for Player ID: " + std::to_string(player->getId()));
        }
    }
}
