/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** HotkeysProtocol.cpp
*/

#include "component/hotkey/HotkeysProtocol.hpp"
#include "component/hotkey/HotkeysManager.hpp"
#include "socket/TcpSocket.hpp"
#include "util/Logger.hpp"

void HotkeysProtocol::processHotkey(std::shared_ptr<Client> client,
                                    SmartBuffer& smartBuffer) {
    if (!client) {
        Logger::error("[HotkeysProtocol] Invalid client reference. Cannot "
                      "process hotkey.");
        return;
    }

    Logger::info("[HotkeysProtocol] Processing hotkey for client.");

    auto player = client->getPlayer();

    if (!player) {
        Logger::warning(
            "[HotkeysProtocol] No player associated with this client.");
        return;
    }

    int32_t playerId = player->getId();

    Logger::info(
        "[HotkeysProtocol] Found player associated with client. Player ID: " +
        std::to_string(playerId));

    int16_t hotkey;

    try {
        smartBuffer >> hotkey;

        Logger::info(
            "[HotkeysProtocol] Received hotkey: " + std::to_string(hotkey) +
            " for Player ID: " + std::to_string(playerId));
    } catch (const std::exception& e) {
        Logger::error("[HotkeysProtocol] Failed to read hotkey from buffer: " +
                      std::string(e.what()));
        return;
    }

    Logger::info(
        "[HotkeysProtocol] Handling hotkey: " + std::to_string(hotkey) +
        " for Player ID: " + std::to_string(playerId));

    HotkeysManager::get().handleHotkey(playerId, hotkey);

    Logger::info("[HotkeysProtocol] Successfully handled hotkey: " +
                 std::to_string(hotkey) +
                 " for Player ID: " + std::to_string(playerId));
}
