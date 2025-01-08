/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Health.hpp
*/

#pragma once

#include "../../util/Config.hpp"

class Health {
  public:
    explicit Health(double health = DEFAULT_HEALTH, int lives = DEFAULT_LIVES);
    ~Health() = default;

    [[nodiscard]] double getHealth() const;
    [[nodiscard]] int getLives() const;
    void takeDamage(double damage);
    void loseLife();
    [[nodiscard]] bool isAlive() const;

  private:
    double _health;
    int _lives;
};
