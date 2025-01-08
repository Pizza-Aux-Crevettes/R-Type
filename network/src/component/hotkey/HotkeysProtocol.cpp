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
    int16_t hotkey;
    smartBuffer >> hotkey;

    auto player = client->getPlayer();
    if (!player) {
        Logger::warning(
            "[HotkeysProtocol] No player associated with this client.");
        return;
    }

    int32_t playerId = player->getId();

    Logger::info("[HotkeysProtocol] Hotkey=" + std::to_string(hotkey) +
                 ", playerId=" + std::to_string(playerId));

    HotkeysManager::get().handleHotkey(playerId, hotkey);
}