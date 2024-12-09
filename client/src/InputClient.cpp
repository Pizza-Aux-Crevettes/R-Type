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

InputClient::InputClient() {
    _keys = {
        {"up", sf::Keyboard::Up},        {"down", sf::Keyboard::Down},
        {"left", sf::Keyboard::Left},    {"right", sf::Keyboard::Right},
        {"attack", sf::Keyboard::Space}, {"auto fire", sf::Keyboard::Enter}};
}

InputClient::~InputClient() {}

sf::Keyboard::Key InputClient::getUp() {
    return (_keys["up"]);
}

void InputClient::setUp(sf::Keyboard::Key new_key) {
    _keys["up"] = new_key;
}

sf::Keyboard::Key InputClient::getDown() {
    return (_keys["down"]);
}

void InputClient::setDown(sf::Keyboard::Key new_key) {
    _keys["down"] = new_key;
}

sf::Keyboard::Key InputClient::getLeft() {
    return (_keys["left"]);
}

void InputClient::setLeft(sf::Keyboard::Key new_key) {
    _keys["left"] = new_key;
}

sf::Keyboard::Key InputClient::getRight() {
    return (_keys["right"]);
}

void InputClient::setRight(sf::Keyboard::Key new_key) {
    _keys["right"] = new_key;
}

sf::Keyboard::Key InputClient::getAttack() {
    return (_keys["attack"]);
}

void InputClient::setAttack(sf::Keyboard::Key new_key) {
    _keys["attack"] = new_key;
}

sf::Keyboard::Key InputClient::getAutoFire() {
    return (_keys["auto fire"]);
}

void InputClient::setAutoFire(sf::Keyboard::Key new_key) {
    _keys["auto fire"] = new_key;
}

void InputClient::checkKey(sf::Event event) {
    for (const auto& [key, value] : _keys)
        if (value == event.key.code)
            std::cout << "J'ai trouvé " << key << "!" << std::endl;
}
