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
 * Protocol: CREATE_PLAYER
 * Payload: playerName (string)
 *
 * Reponse 1 (One client):
 * Protocol: CREATE_PLAYER_CALLBACK
 * Payload: playerId (int32_t), width (int16_t), height (int16_t)
 *
 * Response 2 (All clients):
 * Protocol: CREATE_PLAYER_BROADCAST
 * Payload: playerId (int32_t), playerName (string), width (int16_t), height
 * (int16_t)
 */
void PlayerProtocol::newPlayer(const int clientSocket,
                               SmartBuffer& smartBuffer) {
    std::string name;
    smartBuffer >> name;

    const auto player = PlayerManager::get().createPlayer(name);
    player->setClientSocket(clientSocket);

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(
                       Protocol::OpCode::CREATE_PLAYER_CALLBACK)
                << static_cast<int32_t>(player->getId())
                << static_cast<int16_t>(PLAYER_WIDTH)
                << static_cast<int16_t>(PLAYER_HEIGHT);

    TcpSocket::get().sendToOne(clientSocket, smartBuffer);

    const auto& players = PlayerManager::get().getPlayers();
    for (const auto& existingPlayer : players) {
        smartBuffer.reset();
        smartBuffer << static_cast<int16_t>(
                           Protocol::OpCode::CREATE_PLAYER_BROADCAST)
                    << static_cast<int32_t>(existingPlayer->getId())
                    << std::string{existingPlayer->getName()}
                    << static_cast<int16_t>(PLAYER_WIDTH)
                    << static_cast<int16_t>(PLAYER_HEIGHT);

        UdpSocket::get().sendToAll(smartBuffer);
    }
}

/**
 * @brief Update the player's position and broadcast the update to all clients
 *
 * @param clientAddr The client address
 * @param smartBuffer The SmartBuffer to use for the response
 *
 * Protocol: UPDATE_PLAYERS
 * Payload: playerId (int32_t), posX (int32_t), posY (int32_t)
 */
void PlayerProtocol::sendPlayerPosition(const sockaddr_in& clientAddr,
                                        SmartBuffer& smartBuffer) {

    const auto& players = PlayerManager::get().getPlayers();
    for (const auto& player : players) {
        smartBuffer.reset();
        smartBuffer << static_cast<int16_t>(Protocol::OpCode::UPDATE_PLAYERS)
                    << static_cast<int32_t>(player->getId())
                    << static_cast<int32_t>(player->getPosition().getX())
                    << static_cast<int32_t>(player->getPosition().getY());

        UdpSocket::get().sendToOne(clientAddr, smartBuffer);
    }
}

/**
 * @brief Send a player's score update to all clients
 *
 * @param player The player to update
 *
 * Protocol: UPDATE_PLAYER_INFOS
 * Payload: playerId (int32_t), kills (int16_t), score (int32_t)
 */
void PlayerProtocol::sendPlayerInfosUpdate(
    const std::shared_ptr<Player> player) {
    if (player->getClientAddr().has_value()) {
        SmartBuffer smartBuffer;
        smartBuffer << static_cast<int16_t>(
                           Protocol::OpCode::UPDATE_PLAYER_INFOS)
                    << static_cast<int32_t>(player->getId())
                    << static_cast<int16_t>(player->getKills())
                    << static_cast<int32_t>(player->getScore());

        UdpSocket::get().sendToOne(player->getClientAddr().value(),
                                   smartBuffer);
    }
}
