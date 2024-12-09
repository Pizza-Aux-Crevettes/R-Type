/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** InputClient.hpp
*/

#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <map>

class InputClient {
  private:
    std::map<std::string, sf::Keyboard::Key> _keys;

  public:
    InputClient();
    ~InputClient();
    sf::Keyboard::Key getUp();
    void setUp(sf::Keyboard::Key);
    sf::Keyboard::Key getDown();
    void setDown(sf::Keyboard::Key);
    sf::Keyboard::Key getLeft();
    void setLeft(sf::Keyboard::Key);
    sf::Keyboard::Key getRight();
    void setRight(sf::Keyboard::Key);
    sf::Keyboard::Key getAttack();
    void setAttack(sf::Keyboard::Key);
    sf::Keyboard::Key getAutoFire();
    void setAutoFire(sf::Keyboard::Key);
    void checkKey(sf::Event);
};