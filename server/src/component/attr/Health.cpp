/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Health.cpp
*/

#include "component/attr/Health.hpp"

/**
 * @brief Construct a new Health:: Health object
 *
 * @param health The health
 * @param lives The lives
 */
Health::Health(const double health, const int lives)
    : _health(health), _lives(lives) {}

/**
 * @brief Get the health
 *
 * @return double The health
 */
double Health::getHealth() const {
    return _health;
}

/**
 * @brief Get the lives
 *
 * @return int The lives
 */
int Health::getLives() const {
    return _lives;
}

/**
 * @brief Take damage
 *
 * @param damage The damage to take
 */
void Health::takeDamage(const double damage) {
    _health -= damage;
    if (_health < 0) {
        _health = 0;
    }
}

/**
 * @brief Lose a life
 *
 */
void Health::loseLife() {
    if (_lives > 0) {
        _lives -= 1;
    }
}

/**
 * @brief Check if the entity is alive
 *
 * @return true The entity is alive
 * @return false The entity is dead
 */
bool Health::isAlive() const {
    return _health > 0 || _lives > 0;
}
