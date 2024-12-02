/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Health.cpp
*/

#include "Health.hpp"

double Health::getHealth() const {
    return health;
}

void Health::setHealth(double newHealth) {
    health = newHealth;
}

double Health::getLives() const {
    return lives;
}

void Health::setLives(double newLives) {
    lives = newLives;
}

void Health::reset() {
    health = 100;
    lives = 3;
}

bool Health::isDead() const {
    return health == 0;
}
