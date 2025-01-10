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

/**
 * @brief Construct a new HotkeysManager:: HotkeysManager object
 *
 */
HotkeysManager::HotkeysManager() {
    Logger::success("[HotkeysManager] HotkeysManager initialized.");
    initHotkeys();
}

/**
 * @brief Get the HotkeysManager instance
 *
 * @return HotkeysManager&
 */
HotkeysManager& HotkeysManager::get() {
    static HotkeysManager instance;
    return instance;
}

/**
 * @brief Initialize the hotkeys
 *
 */
void HotkeysManager::initHotkeys() {
    _hotkeyActions = {
        {static_cast<int16_t>(HotkeysCodes::ARROW_LEFT),
         [](int32_t playerId) {
             PlayerManager::get().movePlayer(playerId, -PLAYER_SPEED, 0);
         }},
        {static_cast<int16_t>(HotkeysCodes::ARROW_RIGHT),
         [](int32_t playerId) {
             PlayerManager::get().movePlayer(playerId, PLAYER_SPEED, 0);
         }},
        {static_cast<int16_t>(HotkeysCodes::ARROW_TOP),
         [](int32_t playerId) {
             PlayerManager::get().movePlayer(playerId, 0, -PLAYER_SPEED);
         }},
        {static_cast<int16_t>(HotkeysCodes::ARROW_BOTTOM),
         [](int32_t playerId) {
             PlayerManager::get().movePlayer(playerId, 0, PLAYER_SPEED);
         }}};

    Logger::success("[HotkeysManager] Hotkey actions initialized.");
}

/**
 * @brief Handle a hotkey
 *
 * @param playerId The player ID
 * @param hotkey The hotkey
 */
void HotkeysManager::handleHotkey(int32_t playerId, int16_t hotkey) {
    auto it = _hotkeyActions.find(hotkey);

    if (it != _hotkeyActions.end()) {
        it->second(playerId);
    } else {
        Logger::warning(
            "[HotkeysManager] Unknown hotkey: " + std::to_string(hotkey) +
            " for Player ID: " + std::to_string(playerId));
    }
}
