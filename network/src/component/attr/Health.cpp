/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Health.cpp
*/

#include "component/attr/Health.hpp"

Health::Health(double health, double lives) : _health(health), _lives(lives) {}

double Health::getHealth() const {
    return _health;
}

double Health::getLives() const {
    return _lives;
}

void Health::takeDamage(double damage) {
    _health -= damage;
}

void Health::loseLife() {
    _lives -= 1;
}

bool Health::isAlive() const {
    return _health > 0 || _lives > 0;
}
