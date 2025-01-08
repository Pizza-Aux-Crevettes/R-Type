/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerProtocol.cpp
*/

#include "component/player/PlayerProtocol.hpp"
#include "component/player/PlayerManager.hpp"
#include "protocol/Protocol.hpp"
#include "socket/TcpSocket.hpp"
#include "socket/UdpSocket.hpp"
#include "util/Logger.hpp"

void PlayerProtocol::newPlayer(std::shared_ptr<Client> client, SmartBuffer& smartBuffer)
{
    Logger::info("[PlayerProtocol] Handling new player creation.");

    std::string name;
    smartBuffer >> name;

    Logger::info("[PlayerProtocol] Received new player name: " + name);

    auto player = PlayerManager::get().createPlayer(name);
    if (!player) {
        Logger::error("[PlayerProtocol] Failed to create player with name: " + name);
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
    int udpSocket, const std::vector<std::shared_ptr<Player>>& players,
    const std::shared_ptr<Player>& player, SmartBuffer& smartBuffer)
{
    if (!player) {
        Logger::warning("[PlayerProtocol] Attempted to update position for a null player.");
        return;
    }

    Logger::info("[PlayerProtocol] Sending position update for Player ID: " +
                 std::to_string(player->getId()));

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::PLAYER_UPDATE_POSITION)
                << player->getId()
                << player->getPosition().getX()
                << player->getPosition().getY();

    for (auto& p : players) {
        if (!p) {
            Logger::warning("[PlayerProtocol] Encountered a null player in the players list. Skipping.");
            continue;
        }

        UdpSocket::send(udpSocket, p->getClientAddress(), smartBuffer);

        Logger::info("[PlayerProtocol] Sent position update to Player ID: " +
                     std::to_string(p->getId()) + " at (" +
                     std::to_string(player->getPosition().getX()) + ", " +
                     std::to_string(player->getPosition().getY()) + ").");
    }

    Logger::info("[PlayerProtocol] Position updates sent for Player ID: " +
                 std::to_string(player->getId()));
}