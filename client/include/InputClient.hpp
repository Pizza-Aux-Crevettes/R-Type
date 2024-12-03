/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** InputClient.hpp
*/

#pragma once

#include <SFML/Window/Keyboard.hpp>

class InputClient {
  private:
    sf::Keyboard::Key _up;
    sf::Keyboard::Key _right;
    sf::Keyboard::Key _left;
    sf::Keyboard::Key _down;
    sf::Keyboard::Key _attack;
    sf::Keyboard::Key _autoFire;

  public:
    InputClient();
    ~InputClient();
    sf::Keyboard::Key getUp();
    void setUp();
    sf::Keyboard::Key getRight();
    void setRight();
    sf::Keyboard::Key getLeft();
    void setLeft();
    sf::Keyboard::Key getDown();
    void setDown();
    sf::Keyboard::Key getAttack();
    void setAttack();
    sf::Keyboard::Key getAutoFire();
    void setAutoFire();
};