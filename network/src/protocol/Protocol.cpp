/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Protocol.cpp
*/

/**
 * @file Protocol.cpp
 * @brief Implementation of the Protocol class for handling different operation
 * codes (OpCodes).
 */

#include "protocol/Protocol.hpp"
#include "component/player/PlayerProtocol.hpp"
#include "component/room/RoomProtocol.hpp"
#include "util/Logger.hpp"

/**
 * @brief Retrieves the singleton instance of the Protocol.
 * @return The singleton instance of the Protocol.
 */
Protocol& Protocol::getInstance() {
    static Protocol instance;
    return instance;
}

/**
 * @brief Constructs the Protocol. Currently does nothing.
 */
Protocol::Protocol() {}

/**
 * @brief Destructs the Protocol. Currently does nothing.
 */
Protocol::~Protocol() {}

/**
 * @brief Handles an incoming message by dispatching it to the appropriate
 * handler based on the OpCode.
 * @param clientSocket The client socket that sent the message.
 * @param smartBuffer The buffer containing the message data.
 */
void Protocol::handleMessage(int clientSocket, SmartBuffer& smartBuffer) {
    int16_t opCode;
    smartBuffer >> opCode;

    Logger::info("[Protocol] Handling OpCode: " + std::to_string(opCode));

    switch (opCode) {
    case CREATE_ROOM:
        Logger::trace("[Protocol] Dispatching to RoomProtocol::createRoom");

        RoomProtocol::createRoom(clientSocket, smartBuffer);
        break;

    case JOIN_ROOM:
        Logger::trace("[Protocol] Dispatching to RoomProtocol::joinRoom");

        RoomProtocol::joinRoom(clientSocket, smartBuffer);
        break;

    case DELETE_ROOM:
        Logger::trace("[Protocol] Dispatching to RoomProtocol::deleteRoom");

        RoomProtocol::deleteRoom(clientSocket, smartBuffer);
        break;

    case NEW_PLAYER:
        Logger::trace(
            "[Protocol] Dispatching to PlayerProtocol::createOrGetPlayer");

        PlayerProtocol::newPlayer(clientSocket, smartBuffer);
        break;

    default:
        Logger::error("[Protocol] Received unknown OpCode: " +
                      std::to_string(opCode));

        break;
    }
}
