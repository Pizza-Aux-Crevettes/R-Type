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
 * @param clientAddr The client's address
 *
 * Protocol: NEW_PLAYER
 * Payload: playerName (string)
 */
void PlayerProtocol::newPlayer(const int clientSocket, SmartBuffer& smartBuffer,
                               const sockaddr_in& clientAddr) {
    // Extract buffer data
    std::string name;
    smartBuffer >> name;

    // Create a new player
    const auto player = PlayerManager::get().createPlayer(name);

    Logger::info("[PlayerProtocol] New player created:\n"
                 "  - Name: " +
                 player->getName() +
                 "\n"
                 "  - Player ID: " +
                 std::to_string(player->getId()) +
                 "\n"
                 "  - Client: " +
                 std::string(inet_ntoa(clientAddr.sin_addr)) + ":" +
                 std::to_string(ntohs(clientAddr.sin_port)));

    // Create the response buffer for the new player and send it
    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::NEW_PLAYER_CALLBACK);
    smartBuffer << player->getId();
    TcpSocket::sendToOne(clientSocket, smartBuffer);

    Logger::info("[PlayerProtocol] Sent player ID " +
                 std::to_string(player->getId()) + " to client ");

    // Parse all existing players
    for (const auto& [id, existingPlayer] : PlayerManager::get().getPlayers()) {
        // Create the response buffer for the existing player and send it
        smartBuffer.reset();
        smartBuffer << static_cast<int16_t>(
            Protocol::OpCode::NEW_PLAYER_BROADCAST);
        smartBuffer << existingPlayer->getId()
                    << std::string{existingPlayer->getName()};
        TcpSocket::sendToAll(smartBuffer);

        Logger::info("[PlayerProtocol] Sent existing player ID " +
                     std::to_string(existingPlayer->getId()) +
                     " to new player.");
    }
}

/**
 * @brief Update the player's position and broadcast the update to all clients
 *
 * @param udpSocket The UDP socket
 * @param players The list of all players
 * @param player The player to update
 * @param smartBuffer The SmartBuffer to use for the response
 *
 * Protocol: PLAYER_UPDATE_POSITION
 * Payload: playerId (int32_t), posX (int16_t), posY (int16_t)
 */
void PlayerProtocol::updatePos(
    const int udpSocket, const std::vector<std::shared_ptr<Player>>& players,
    const std::shared_ptr<Player>& player, SmartBuffer& smartBuffer) {
    // Create the response buffer
    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(
                       Protocol::OpCode::PLAYER_UPDATE_POSITION)
                << player->getId() << player->getPosition().getX()
                << player->getPosition().getY();

    // Broadcast the position update to all clients
    UdpSocket::send(udpSocket, player->getClientAddress(), smartBuffer);

    Logger::info("[PlayerProtocol] Position update sent:\n"
                 "  - Player ID: " +
                 std::to_string(player->getId()) +
                 "\n"
                 "  - Position: (" +
                 std::to_string(player->getPosition().getX()) + ", " +
                 std::to_string(player->getPosition().getY()) + ")");
}
