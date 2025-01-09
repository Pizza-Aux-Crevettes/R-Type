/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** HotkeysProtocol.cpp
*/

#include "component/hotkey/HotkeysProtocol.hpp"
#include "component/hotkey/HotkeysManager.hpp"
#include "util/Logger.hpp"

/**
 * @brief Process a hotkey
 *
 * @param clientSocket The client socket
 * @param smartBuffer The smart buffer
 */
void HotkeysProtocol::processHotkey(int clientSocket,
                                    SmartBuffer& smartBuffer) {
    int32_t playerId;
    int16_t hotkey;
    smartBuffer >> playerId >> hotkey;

    HotkeysManager::get().handleHotkey(playerId, hotkey);
}
