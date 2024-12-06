/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Protocol.cpp
*/

#include "protocol/Protocol.hpp"
#include "util/Logger.hpp"

Protocol::Protocol() {
    Logger::info("[Protocol] Instance successfully created.");
}

Protocol::~Protocol() {
    Logger::info("[Protocol] Instance successfully destroyed.");
}

void Protocol::handleMessage(int clientSocket, SmartBuffer& smartBuffer) {
    uint8_t opCode;
    smartBuffer >> opCode;

    Logger::info("[Protocol] Handling OpCode: " + std::to_string(opCode));

    switch (opCode) {
    case CREATE_ROOM:
        createRoom(clientSocket, smartBuffer);
        break;
    case JOIN_ROOM:
        joinRoom(clientSocket, smartBuffer);
        break;
    case DELETE_ROOM:
        deleteRoom(clientSocket, smartBuffer);
        break;
    default:
        Logger::error("[Protocol] Received unknown OpCode: " +
                      std::to_string(opCode));
        break;
    }
}

void Protocol::createRoom(int clientSocket, SmartBuffer& smartBuffer) {
    /*
     * Protocol CREATE_ROOM
     * int8_t opCode
     * Data sent in response: CREATE_ROOM_CALLBACK
     */
    Logger::trace(
        "[Protocol] Processing CREATE_ROOM command (no data required).");
}

void Protocol::joinRoom(int clientSocket, SmartBuffer& smartBuffer) {
    /*
     * Protocol JOIN_ROOM:
     * int8_t opCode
     * int32_t roomCode
     * Data sent in response: JOIN_ROOM_CALLBACK
     */
    int32_t roomCode;
    smartBuffer >> roomCode;

    Logger::trace("[Protocol] Processing JOIN_ROOM command. roomCode = " +
                  std::to_string(roomCode));
}

void Protocol::deleteRoom(int clientSocket, SmartBuffer& smartBuffer) {
    /*
     * Protocol DELETE_ROOM:
     * int8_t opCode
     * int32_t roomCode
     * Data sent in response: DELETE_ROOM_CALLBACK
     */
    int32_t roomCode;
    smartBuffer >> roomCode;

    Logger::trace("[Protocol] Processing DELETE_ROOM command. roomCode = " +
                  std::to_string(roomCode));
}
