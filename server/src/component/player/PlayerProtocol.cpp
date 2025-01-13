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

/**
 * @brief Create a new player and broadcast it to all clients
 *
 * @param clientSocket The client's TCP socket
 * @param smartBuffer The SmartBuffer to use for the response
 *
 * Protocol: NEW_PLAYER
 * Payload: playerName (string)
 */
void PlayerProtocol::newPlayer(const int clientSocket,
                               SmartBuffer& smartBuffer) {
    std::string name;
    smartBuffer >> name;

    const auto player = PlayerManager::get().createPlayer(name);
    player->setClientSocket(clientSocket);

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::NEW_PLAYER_CALLBACK)
                << static_cast<int32_t>(player->getId());

    TcpSocket::get().sendToOne(clientSocket, smartBuffer);

    Logger::packet("[PlayerProtocol] Sent player ID " +
                   std::to_string(player->getId()) + " to client ");

    for (const auto& [id, existingPlayer] : PlayerManager::get().getPlayers()) {
        smartBuffer.reset();
        smartBuffer << static_cast<int16_t>(
                           Protocol::OpCode::NEW_PLAYER_BROADCAST)
                    << static_cast<int32_t>(existingPlayer->getId())
                    << std::string{existingPlayer->getName()};

        UdpSocket::get().sendToAll(smartBuffer);

        Logger::packet("[PlayerProtocol] Sent existing player ID " +
                       std::to_string(existingPlayer->getId()) +
                       " to new player.");
    }
}

/**
 * @brief Update the player's position and broadcast the update to all clients
 *
 * @param clientAddr The client address
 * @param smartBuffer The SmartBuffer to use for the response
 *
 * Protocol: PLAYER_POSITION_UPDATE
 * Payload: playerId (int32_t), posX (int32_t), posY (int32_t)
 */
void PlayerProtocol::sendPlayerPosition(const sockaddr_in& clientAddr,
                                        SmartBuffer& smartBuffer) {

    const auto& players = PlayerManager::get().getPlayers();
    for (const auto& [id, player] : players) {
        smartBuffer.reset();
        smartBuffer << static_cast<int16_t>(
                           Protocol::OpCode::PLAYER_POSITION_UPDATE)
                    << static_cast<int32_t>(player->getId())
                    << static_cast<int32_t>(player->getPosition().getX())
                    << static_cast<int32_t>(player->getPosition().getY());

        UdpSocket::get().sendToOne(clientAddr, smartBuffer);

        Logger::packet("[PlayerProtocol] Position update sent:\n"
                       "  - Player ID: " +
                       std::to_string(player->getId()) +
                       "\n"
                       "  - Position: (" +
                       std::to_string(player->getPosition().getX()) + ", " +
                       std::to_string(player->getPosition().getY()) + ")");
    }
}

/**
 * @brief Delete a player and broadcast the deletion to all clients
 *
 * @param playerId The player's ID
 *
 * Protocol: PLAYER_DELETED
 * Payload: playerId (int32_t)
 */
void PlayerProtocol::sendPlayerDeleted(const int32_t playerId) {
    SmartBuffer smartBuffer;

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::PLAYER_DELETED)
                << static_cast<int32_t>(playerId);

    UdpSocket::get().sendToAll(smartBuffer);

    Logger::packet("[PlayerProtocol] Player deleted sent:\n"
                   "  - Player ID: " +
                   std::to_string(playerId));
}
