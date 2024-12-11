/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Health.cpp
*/

/**
 * @file Health.cpp
 * @brief Implements the Health class, which manages health points and lives for
 * a player or entity.
 */

#include "component/attr/Health.hpp"

/**
 * @brief Constructs a Health object with initial health points and lives.
 *
 * @param health The initial health points.
 * @param lives The initial number of lives.
 */
Health::Health(double health, int lives) : _health(health), _lives(lives) {}

/**
 * @brief Destructor for Health.
 */
Health::~Health() {}

/**
 * @brief Retrieves the current health points.
 *
 * @return The current health points as a double.
 */
double Health::getHealth() const {
    return _health;
}

/**
 * @brief Retrieves the current number of lives.
 *
 * @return The current number of lives as an integer.
 */
int Health::getLives() const {
    return _lives;
}

/**
 * @brief Reduces the health by a specified amount of damage.
 *
 * If the resulting health falls below zero, it is clamped to zero.
 *
 * @param damage The amount of damage to apply.
 */
void Health::takeDamage(double damage) {

    _health -= damage;
    if (_health < 0) {
        _health = 0;
    }
}

/**
 * @brief Reduces the number of lives by one.
 *
 * If the number of lives becomes negative, it remains unchanged (non-negative
 * constraint).
 */
void Health::loseLife() {
    if (_lives > 0) {
        _lives -= 1;
    }
}

/**
 * @brief Checks if the entity is still alive.
 *
 * An entity is considered alive if it has either health points greater than
 * zero or at least one life remaining.
 *
 * @return True if the entity is alive, false otherwise.
 */
bool Health::isAlive() const {
    return _health > 0 || _lives > 0;
}
