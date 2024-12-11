/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerProtocol.cpp
*/

/**
 * @file PlayerProtocol.cpp
 * @brief Handles player-related protocols, such as creating or retrieving a
 * player.
 */
#include "component/player/PlayerProtocol.hpp"
#include "component/player/PlayerManager.hpp"
#include "socket/TcpSocket.hpp"
#include "util/Logger.hpp"

/**
 * Protocol Details:
 * - Input: std:string name
 * - Output: int16_t opCode (NEW_PLAYER_CALLBACK) << int32_t playerId
 */
void PlayerProtocol::newPlayer(int clientSocket, SmartBuffer& smartBuffer) {
    std::string name;

    smartBuffer >> name;
    smartBuffer.reset();
    smartBuffer << int16_t(Protocol::OpCode::NEW_PLAYER_CALLBACK);

    if (name.empty()) {
        name = "Player" +
               std::to_string(PlayerManager::getInstance().getPlayers().size() +
                              1);
    }

    auto player = PlayerManager::getInstance().createPlayerByThread(name);

    smartBuffer << player->getId();

    TcpSocket::sendTcp(clientSocket, smartBuffer);

    Logger::info("[PlayerProtocol] Assigned player ID " +
                 std::to_string(player->getId()) + " to client.");
}
