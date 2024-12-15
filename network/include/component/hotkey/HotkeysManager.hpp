/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** HotkeysManager.hpp
*/

#pragma once

#include <unordered_map>
#include <functional>
#include <cstdint>

class HotkeysManager {
public:
    static HotkeysManager& getInstance();

    void handleHotkey(int32_t playerId, int16_t hotkey);

private:
    HotkeysManager();
    ~HotkeysManager() = default;

    void initHotkeys();
    static void handlePlayerPosition(int32_t playerId, int deltaX, int deltaY);

    std::unordered_map<int16_t, std::function<void(int32_t)>> _hotkeyActions;
};
