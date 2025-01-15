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

/**
 * @brief Construct a new Protocol:: Protocol object
 *
 */
Protocol& Protocol::get() {
    static Protocol instance;
    return instance;
}

/**
 * @brief Handle a message received from a client
 *
 * @param clientSocket The client's socket
 * @param smartBuffer The SmartBuffer containing the message
 * @param clientAddr The client's address
 */
void Protocol::handleMessage(const int clientSocket, SmartBuffer& smartBuffer) {
    if (smartBuffer.getSize() < sizeof(int16_t)) {
        Logger::warning(
            "[Protocol] Received invalid message with insufficient size.");
        return;
    }

    int16_t opCode;
    smartBuffer >> opCode;

    switch (static_cast<OpCode>(opCode)) {
    case DEFAULT:
        Logger::warning("[Protocol] DEFAULT OpCode received. No action taken.");
        break;

    case CREATE_PLAYER:
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
