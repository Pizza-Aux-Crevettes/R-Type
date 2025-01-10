/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** HotkeysManager.hpp
*/

#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>

class HotkeysManager {
  public:
    HotkeysManager(const HotkeysManager&) = delete;
    HotkeysManager& operator=(const HotkeysManager&) = delete;

    static HotkeysManager& get();

    void handleHotkey(int32_t playerId, int16_t hotkey);

  private:
    HotkeysManager();
    ~HotkeysManager() = default;

    void initHotkeys();
    static void handlePlayerPosition(int32_t playerId, int32_t deltaX,
                                     int32_t deltaY);

    std::unordered_map<int16_t, std::function<void(int32_t)>> _hotkeyActions;
};
