/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Protocol.cpp
*/

#include "protocol/Protocol.hpp"
#include "component/hotkey/HotkeysProtocol.hpp"
#include "component/player/PlayerProtocol.hpp"
#include "util/Logger.hpp"

Protocol& Protocol::get() {
    static Protocol instance;
    return instance;
}

void Protocol::handleMessage(const int clientSocket, SmartBuffer& smartBuffer,
                             const sockaddr_in& clientAddr) {
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

    case NEW_PLAYER:
        Logger::info("[Protocol] NEW_PLAYER operation.");
        PlayerProtocol::newPlayer(clientSocket, smartBuffer, clientAddr);
        break;

    case HOTKEY_PRESSED:
        Logger::info("[Protocol] HOTKEY_PRESSED operation.");
        HotkeysProtocol::processHotkey(clientSocket, smartBuffer);
        break;

    default:
        Logger::error("[Protocol] Received unknown OpCode: " +
                      std::to_string(opCode));
        break;
    }
}