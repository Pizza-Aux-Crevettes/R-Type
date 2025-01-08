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

void Protocol::handleMessage(std::shared_ptr<Client> client,
                             SmartBuffer& smartBuffer) {
    if (smartBuffer.getSize() < sizeof(int16_t)) {
        return;
    }

    int16_t opCode;
    smartBuffer >> opCode;

    switch (static_cast<OpCode>(opCode)) {
    case DEFAULT:
        break;
    case CREATE_ROOM:
        RoomProtocol::createRoom(client, smartBuffer);
        break;
    case JOIN_ROOM:
        RoomProtocol::joinRoom(client, smartBuffer);
        break;
    case DELETE_ROOM:
        RoomProtocol::deleteRoom(client, smartBuffer);
        break;
    case NEW_PLAYER:
        PlayerProtocol::newPlayer(client, smartBuffer);
        break;
    case HOTKEY_PRESSED:
        HotkeysProtocol::processHotkey(client, smartBuffer);
        break;
    case START_GAME:
        RoomProtocol::startGame(client, smartBuffer);
        break;
    case STOP_GAME:
        RoomProtocol::stopGame(client, smartBuffer);
        break;
    default:
        Logger::error("[Protocol] Received unknown OpCode: " +
                      std::to_string(opCode));
        break;
    }
}
