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

    // Create the response buffer for the new player
    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::NEW_PLAYER_CALLBACK);
    smartBuffer << player->getId();

    // Send the player ID to the client that requested it
    TcpSocket::sendToOne(clientSocket, smartBuffer);

    Logger::packet("[PlayerProtocol] Sent player ID " +
                   std::to_string(player->getId()) + " to client ");

    // Parse all existing players
    for (const auto& [id, existingPlayer] : PlayerManager::get().getPlayers()) {
        // Create the response buffer for the existing player
        smartBuffer.reset();
        smartBuffer << static_cast<int16_t>(
            Protocol::OpCode::NEW_PLAYER_BROADCAST);
        smartBuffer << existingPlayer->getId()
                    << std::string{existingPlayer->getName()};

        // Send the existing player to the new player
        TcpSocket::sendToAll(smartBuffer);

        Logger::packet("[PlayerProtocol] Sent existing player ID " +
                       std::to_string(existingPlayer->getId()) +
                       " to new player.");

        // Sleep for a short time to avoid packet loss
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

/**
 * @brief Update the player's position and broadcast the update to all clients
 *
 * @param udpSocket The UDP socket
 * @param player The player to update
 * @param smartBuffer The SmartBuffer to use for the response
 *
 * Protocol: PLAYER_POSITION_UPDATE
 * Payload: playerId (int32_t), posX (int16_t), posY (int16_t)
 */
void PlayerProtocol::sendPositionsUpdate(const int udpSocket,
                                         const sockaddr_in& client,
                                         const std::shared_ptr<Player>& player,
                                         SmartBuffer& smartBuffer) {
    // Create the response buffer
    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(
        Protocol::OpCode::PLAYER_POSITION_UPDATE);
    smartBuffer << player->getId();
    smartBuffer << player->getPosition().getX();
    smartBuffer << player->getPosition().getY();

    // Broadcast the position update to all clients
    UdpSocket::send(udpSocket, client, smartBuffer);

    Logger::packet("[PlayerProtocol] Position update sent:\n"
                   "  - Player ID: " +
                   std::to_string(player->getId()) +
                   "\n"
                   "  - Position: (" +
                   std::to_string(player->getPosition().getX()) + ", " +
                   std::to_string(player->getPosition().getY()) + ")");
}
