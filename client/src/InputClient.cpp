/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Implements the logic for processing user inputs on the client side.
** Handles inputs from devices such as the keyboard or mouse, converting them
*into game actions.
** Responsibility:
** - Capture and interpret user inputs.
** - Relay interpreted inputs to the appropriate systems in the game.
** - Change touch for mouse clicks.
** InputClient.cpp
*/

#include "InputClient.hpp"

InputClient::InputClient() {}

InputClient::~InputClient() {}

sf::Keyboard::Key InputClient::getUp() {
    return (_up);
}

void InputClient::setUp() {}

sf::Keyboard::Key InputClient::getRight() {
    return (_right);
}

void InputClient::setRight() {}

sf::Keyboard::Key InputClient::getLeft() {
    return (_left);
}

void InputClient::setLeft() {}

sf::Keyboard::Key InputClient::getDown() {
    return (_down);
}

void InputClient::setDown() {}

sf::Keyboard::Key InputClient::getAttack() {
    return (_attack);
}

void InputClient::setAttack() {}

sf::Keyboard::Key InputClient::getAutoFire() {
    return (_autoFire);
}

void InputClient::setAutoFire() {}