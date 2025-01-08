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
        Logger::warning(
            "[Protocol] Received invalid message with insufficient size.");
        return;
    }

    int16_t opCode;
    smartBuffer >> opCode;

    Logger::info("[Protocol] Handling message with OpCode: " +
                 std::to_string(opCode));

    switch (static_cast<OpCode>(opCode)) {
    case DEFAULT:
        Logger::warning("[Protocol] DEFAULT OpCode received. No action taken.");
        break;

    case CREATE_ROOM:
        Logger::info("[Protocol] CREATE_ROOM operation.");
        RoomProtocol::createRoom(client, smartBuffer);
        break;

    case JOIN_ROOM:
        Logger::info("[Protocol] JOIN_ROOM operation.");
        RoomProtocol::joinRoom(client, smartBuffer);
        break;

    case DELETE_ROOM:
        Logger::info("[Protocol] DELETE_ROOM operation.");
        RoomProtocol::deleteRoom(client, smartBuffer);
        break;

    case NEW_PLAYER:
        Logger::info("[Protocol] NEW_PLAYER operation.");
        PlayerProtocol::newPlayer(client, smartBuffer);
        break;

    case HOTKEY_PRESSED:
        Logger::info("[Protocol] HOTKEY_PRESSED operation.");
        HotkeysProtocol::processHotkey(client, smartBuffer);
        break;

    case START_GAME:
        Logger::info("[Protocol] START_GAME operation.");
        RoomProtocol::startGame(client, smartBuffer);
        break;

    case STOP_GAME:
        Logger::info("[Protocol] STOP_GAME operation.");
        RoomProtocol::stopGame(client, smartBuffer);
        break;

    default:
        Logger::error("[Protocol] Received unknown OpCode: " +
                      std::to_string(opCode));
        break;
    }
}