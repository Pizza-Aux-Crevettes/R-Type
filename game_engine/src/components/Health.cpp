/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Health.cpp
**
** The Health class represents the health system of an entity in the game.
** It tracks the current health (currentHp) and the maximum health (maxHp)
** of the entity. The constructor allows initializing the current health
** with a specified value, while the maximum health is fixed at 100.
*/

#include "components/Health.hpp"

Health::Health(int initialHp) : _currentHp(initialHp), _maxHp(100) {}

Health::~Health() {}

int Health::getCurrentHp() const {
    return this->_currentHp;
}

void Health::setCurrentHp(int currentHp) {
    this->_currentHp = currentHp;
}

int Health::getMaxHp() const {
    return this->_maxHp;
}

void Health::setMaxHp(int maxHp) {
    this->_maxHp = maxHp;
}
