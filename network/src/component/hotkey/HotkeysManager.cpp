/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** HotkeysManager.cpp
*/

#include "component/hotkey/HotkeysManager.hpp"
#include "component/hotkey/HotkeysCodes.hpp"
#include "component/player/PlayerManager.hpp"
#include "util/Logger.hpp"

HotkeysManager::HotkeysManager() {
    Logger::info("[HotkeysManager] Initializing HotkeysManager.");

    initHotkeys();

    Logger::info("[HotkeysManager] HotkeysManager successfully initialized.");
}

HotkeysManager& HotkeysManager::get() {
    static HotkeysManager instance;
    return instance;
}

void HotkeysManager::initHotkeys() {
    Logger::info("[HotkeysManager] Initializing hotkey actions.");

    _hotkeyActions = {
        {static_cast<int16_t>(HotkeysCodes::ARROW_LEFT),
         [this](int32_t playerId) { handlePlayerPosition(playerId, -1, 0); }},
        {static_cast<int16_t>(HotkeysCodes::ARROW_RIGHT),
         [this](int32_t playerId) { handlePlayerPosition(playerId, 1, 0); }},
        {static_cast<int16_t>(HotkeysCodes::ARROW_TOP),
         [this](int32_t playerId) { handlePlayerPosition(playerId, 0, -1); }},
        {static_cast<int16_t>(HotkeysCodes::ARROW_BOTTOM),
         [this](int32_t playerId) { handlePlayerPosition(playerId, 0, 1); }}};

    Logger::info("[HotkeysManager] Hotkey actions initialized successfully.");
}

void HotkeysManager::handleHotkey(int32_t playerId, int16_t hotkey) {
    Logger::info("[HotkeysManager] Handling hotkey: " + std::to_string(hotkey) +
                 " for Player ID: " + std::to_string(playerId));

    auto it = _hotkeyActions.find(hotkey);

    if (it != _hotkeyActions.end()) {
        it->second(playerId);
    } else {
        Logger::warning("[HotkeysManager] Unknown hotkey: " +
                        std::to_string(hotkey));
    }
}

void HotkeysManager::handlePlayerPosition(int32_t playerId, int offsetX,
                                          int offsetY) {
    try {
        Logger::info("[HotkeysManager] Updating position for Player ID: " +
                     std::to_string(playerId) + " with offset (" +
                     std::to_string(offsetX) + ", " + std::to_string(offsetY) +
                     ").");

        auto player = PlayerManager::get().findPlayerById(playerId);

        if (!player) {
            Logger::warning("[HotkeysManager] Player " +
                            std::to_string(playerId) + " not found.");
            return;
        }

        Point currentPos = player->getPosition();
        Point newPos(currentPos.getX() + offsetX, currentPos.getY() + offsetY);

        player->setPosition(newPos);

        Logger::info("[HotkeysManager] Player " + std::to_string(playerId) +
                     " moved to position (" + std::to_string(newPos.getX()) +
                     ", " + std::to_string(newPos.getY()) + ").");
    } catch (const std::exception& e) {
        Logger::error(
            "[HotkeysManager] Failed to update position for Player ID: " +
            std::to_string(playerId) + ". Error: " + e.what());
    }
}