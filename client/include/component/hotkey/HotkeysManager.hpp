/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** HotkeysManager.hpp
*/

#pragma once

#include <SFML/Window.hpp>
#include <unordered_map>
#include <map>
#include "component/hotkey/HotkeysCodes.hpp"

class HotkeysManager {
  public:
    HotkeysManager();
    ~HotkeysManager();

    static HotkeysManager& get();

    void checkKey(const sf::Event& event);
    bool isKeyUsed(sf::Keyboard::Key key);
    std::string keyToString(sf::Keyboard::Key key);

    void setBottom(sf::Keyboard::Key);
    void setTop(sf::Keyboard::Key);
    void setLeft(sf::Keyboard::Key);
    void setRight(sf::Keyboard::Key);
    void setShoot(sf::Keyboard::Key);
    void setAutoFire(sf::Keyboard::Key);

    sf::Keyboard::Key getBottom();
    sf::Keyboard::Key getTop();
    sf::Keyboard::Key getLeft();
    sf::Keyboard::Key getRight();
    sf::Keyboard::Key getShoot();
    sf::Keyboard::Key getAutoFire();

  private:
    sf::Keyboard::Key _bottom = sf::Keyboard::Down;
    sf::Keyboard::Key _top = sf::Keyboard::Up;
    sf::Keyboard::Key _left = sf::Keyboard::Left;
    sf::Keyboard::Key _right = sf::Keyboard::Right;
    sf::Keyboard::Key _shoot = sf::Keyboard::Space;
    sf::Keyboard::Key _autoFire = sf::Keyboard::Enter;
};