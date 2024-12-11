/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Protocol.cpp
*/

#include "protocol/Protocol.hpp"
#include "component/player/PlayerProtocol.hpp"
#include "component/room/RoomProtocol.hpp"
#include "util/Logger.hpp"

Protocol& Protocol::getInstance() {
    static Protocol instance;
    return instance;
}

Protocol::Protocol() {}

Protocol::~Protocol() {}

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
        Logger::trace("[Protocol] Dispatching to PlayerProtocol::newPlayer");

        PlayerProtocol::newPlayer(clientSocket, smartBuffer);
        break;

    default:
        Logger::error("[Protocol] Received unknown OpCode: " +
                      std::to_string(opCode));

        break;
    }
}
