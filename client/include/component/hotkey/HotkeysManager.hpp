/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** HotkeysManager.hpp
*/

#pragma once

#include "component/hotkey/HotkeysCodes.hpp"
#include <SFML/Window.hpp>
#include <unordered_map>

class HotkeysManager {
  public:
    HotkeysManager();
    ~HotkeysManager();

    sf::Keyboard::Key getKey(HotkeysCodes hotkey);
    void setKey(HotkeysCodes hotkey, sf::Keyboard::Key newKey);

    void checkKey(const sf::Event& event);

  private:
    std::unordered_map<HotkeysCodes, sf::Keyboard::Key> _keys;
};