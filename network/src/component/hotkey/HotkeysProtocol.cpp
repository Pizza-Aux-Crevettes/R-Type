/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** HotkeysProtocol.cpp
*/

#include "component/hotkey/HotkeysProtocol.hpp"
#include "component/hotkey/HotkeysManager.hpp"
#include "util/Logger.hpp"

void HotkeysProtocol::processHotkey(int clientSocket,
                                    SmartBuffer& smartBuffer) {
    int32_t playerId;
    int16_t hotkey;

    smartBuffer >> playerId >> hotkey;

    Logger::info("[HotkeysProtocol] Processing hotkey " +
                 std::to_string(hotkey) + " for player " +
                 std::to_string(playerId));

    HotkeysManager::getInstance().handleHotkey(playerId, hotkey);
}
