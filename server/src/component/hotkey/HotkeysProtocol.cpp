/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** HotkeysProtocol.cpp
*/

#include "component/hotkey/HotkeysProtocol.hpp"
#include "component/hotkey/HotkeysManager.hpp"
#include "component/player/PlayerManager.hpp"
#include "util/Logger.hpp"

/**
 * @brief Process a hotkey
 *
 * @param clientSocket The client socket
 * @param smartBuffer The smart buffer
 * @param clientAddr The client's address
 */
void HotkeysProtocol::processHotkey(int clientSocket,
                                    SmartBuffer& smartBuffer, const sockaddr_in& clientAddr) {
    int32_t playerId;
    int16_t hotkey;
    smartBuffer >> playerId >> hotkey;

    HotkeysManager::get().handleHotkey(playerId, hotkey);

    if (PlayerManager::get().findByID(playerId) == nullptr) {
        Logger::warning("[HotkeysProtocol] Player not found. Player ID: " + std::to_string(playerId));
        return;
    }
    PlayerManager::get().findByID(playerId)->setClientAddr(clientAddr);
}
