/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Protocol.cpp
*/

#include "protocol/Protocol.hpp"
#include "component/room/RoomProtocol.hpp"
#include "util/Logger.hpp"

Protocol& Protocol::getInstance() {
    static Protocol instance;
    return instance;
}

Protocol::Protocol() {}

Protocol::~Protocol() {}

void Protocol::handleMessage(int clientSocket, SmartBuffer& smartBuffer) {
    int8_t opCode;
    smartBuffer >> opCode;

    Logger::info("[Protocol] Handling OpCode: " + std::to_string(opCode));

    switch (opCode) {
    case CREATE_ROOM:
        RoomProtocol::createRoom(clientSocket, smartBuffer);
        break;
    case JOIN_ROOM:
        RoomProtocol::joinRoom(clientSocket, smartBuffer);
        break;
    case DELETE_ROOM:
        RoomProtocol::deleteRoom(clientSocket, smartBuffer);
        break;
    default:
        Logger::error("[Protocol] Received unknown OpCode: " +
                      std::to_string(opCode));

        break;
    }
}
