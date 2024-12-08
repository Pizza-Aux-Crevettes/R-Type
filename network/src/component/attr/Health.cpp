/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Health.cpp
*/

#include "component/attr/Health.hpp"
#include "util/Logger.hpp"

Health::Health(double health, int lives) : _health(health), _lives(lives) {
    Logger::info("[Health] Initialized with " + std::to_string(health) +
                 " health and " + std::to_string(lives) + " lives.");
}

Health::~Health() {
    Logger::info("[Health] Health component destroyed.");
}

double Health::getHealth() const {
    Logger::debug("[Health] Current health: " + std::to_string(_health));

    return _health;
}

int Health::getLives() const {
    Logger::debug("[Health] Current lives: " + std::to_string(_lives));

    return _lives;
}

void Health::takeDamage(double damage) {
    Logger::info("[Health] Taking damage: " + std::to_string(damage));

    _health -= damage;
    if (_health < 0) {
        _health = 0;

        Logger::warning("[Health] Health dropped to 0.");
    } else {
        Logger::info("[Health] Health reduced to: " + std::to_string(_health));
    }
}

void Health::loseLife() {
    Logger::info("[Health] Losing one life. Remaining lives: " +
                 std::to_string(_lives - 1));

    _lives -= 1;
    if (_lives < 0) {
        Logger::warning("[Health] Lives dropped below 0.");
    }
}

bool Health::isAlive() const {
    bool alive = _health > 0 || _lives > 0;

    Logger::debug("[Health] Checking if alive: " +
                  std::string(alive ? "Yes" : "No"));

    return alive;
}
