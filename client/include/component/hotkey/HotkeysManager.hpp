/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** HotkeysManager.hpp
*/

#pragma once

#include <SFML/Window.hpp>
#include <unordered_map>
#include "component/hotkey/HotkeysCodes.hpp"

class HotkeysManager {
  public:
    HotkeysManager();
    ~HotkeysManager();

    static HotkeysManager& get();

    sf::Keyboard::Key getKey(HotkeysCodes hotkey);
    void setKey(HotkeysCodes hotkey, sf::Keyboard::Key newKey);

    void checkKey(const sf::Event& event);
    bool isKeyUsed(sf::Keyboard::Key key);
    std::string keyToString(sf::Keyboard::Key key);
    void isAutoFire(HotkeysCodes code);
    bool getAutoFireState();

  private:
    std::unordered_map<HotkeysCodes, sf::Keyboard::Key> _keys;
    bool _autofire;
};