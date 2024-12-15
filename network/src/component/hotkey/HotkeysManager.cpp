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

HotkeysManager& HotkeysManager::get() {
    static HotkeysManager instance;
    return instance;
}

HotkeysManager::HotkeysManager() {
    initHotkeys();
}

void HotkeysManager::initHotkeys() {
    _hotkeyActions = {{static_cast<int16_t>(HotkeysCodes::ARROW_LEFT),
                       [this](const int32_t playerId) {
                           handlePlayerPosition(playerId, -1, 0);
                       }},
                      {static_cast<int16_t>(HotkeysCodes::ARROW_RIGHT),
                       [this](const int32_t playerId) {
                           handlePlayerPosition(playerId, 1, 0);
                       }},
                      {static_cast<int16_t>(HotkeysCodes::ARROW_TOP),
                       [this](const int32_t playerId) {
                           handlePlayerPosition(playerId, 0, -1);
                       }},
                      {static_cast<int16_t>(HotkeysCodes::ARROW_BOTTOM),
                       [this](const int32_t playerId) {
                           handlePlayerPosition(playerId, 0, 1);
                           ;
                       }}};
}

void HotkeysManager::handleHotkey(const int32_t playerId,
                                  const int16_t hotkey) {
    if (const auto it = _hotkeyActions.find(hotkey);
        it != _hotkeyActions.end()) {
        it->second(playerId);
    } else {
        Logger::warning("[HotkeysManager] Unknown hotkey: " +
                        std::to_string(hotkey));
    }
}

void HotkeysManager::handlePlayerPosition(const int32_t playerId,
                                          const int deltaX, const int deltaY) {
    try {
        const auto player = PlayerManager::get().findPlayerById(playerId);
        const Point& currentPosition = player->getPosition();
        Point newPosition = currentPosition;
        newPosition.setPoint(currentPosition.getX() + deltaX,
                             currentPosition.getY() + deltaY);

        player->setPosition(newPosition);

        Logger::info("[HotkeysManager] Player " + std::to_string(playerId) +
                     " moved to position (" +
                     std::to_string(newPosition.getX()) + ", " +
                     std::to_string(newPosition.getY()) + ").");
    } catch (const std::exception& e) {
        Logger::error("[HotkeysManager] Failed to handle position for player " +
                      std::to_string(playerId) + ": " + e.what());
    }
}
