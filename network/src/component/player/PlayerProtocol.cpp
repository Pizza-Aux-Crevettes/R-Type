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
 * @brief Processes the NEW_PLAYER protocol. Assigns a player ID to the client,
 *        either by reusing an existing player for the thread or creating a new
 * one.
 *
 * Protocol Details:
 * - Input: None
 * - Output:
 *   - OpCode: NEW_PLAYER_CALLBACK
 *   - int32_t: Assigned player ID
 *
 * @param clientSocket The socket associated with the client.
 * @param smartBuffer The buffer for receiving and sending data.
 */
void PlayerProtocol::newPlayer(int clientSocket, SmartBuffer& smartBuffer) {
    // Protocol structure (EMPTY)
    //

    // Get the data from SmartBuffer after injection (EMPTY)
    //

    // Reset and init for response
    smartBuffer.reset();
    smartBuffer << int8_t(Protocol::OpCode::NEW_PLAYER_CALLBACK);

    // Check relevant data
    auto player =
        PlayerManager::getInstance().createPlayerByThread("NewPlayer");

    // Response (CALLBACK) with status
    smartBuffer << player->getId();

    // Send back the data to client
    TcpSocket::sendTcp(clientSocket, smartBuffer);

    Logger::info("[PlayerProtocol] Assigned player ID " +
                 std::to_string(player->getId()) + " to client.");
}
