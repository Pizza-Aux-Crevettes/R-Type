/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Protocol.cpp
*/

#include "protocol/Protocol.hpp"
#include "component/hotkey/HotkeysProtocol.hpp"
#include "component/player/PlayerProtocol.hpp"
#include "component/room/RoomProtocol.hpp"
#include "util/Logger.hpp"

Protocol& Protocol::get() {
    static Protocol instance;

    return instance;
}

void Protocol::handleMessage(const int clientSocket, SmartBuffer& smartBuffer) {
    int16_t opCode;

    smartBuffer >> opCode;

    switch (opCode) {
    case DEFAULT:
        break;
    case CREATE_ROOM:
        RoomProtocol::createRoom(clientSocket, smartBuffer);
        break;
    case JOIN_ROOM:
        RoomProtocol::joinRoom(clientSocket, smartBuffer);
        break;
    case DELETE_ROOM:
        RoomProtocol::deleteRoom(clientSocket, smartBuffer);
        break;
    case NEW_PLAYER:
        PlayerProtocol::newPlayer(clientSocket, smartBuffer);
        break;
    case HOTKEY_PRESSED:
        HotkeysProtocol::processHotkey(clientSocket, smartBuffer);
        break;
    default:
        Logger::error("[Protocol] Received unknown OpCode: " +
                      std::to_string(opCode));
        break;
    }
}
