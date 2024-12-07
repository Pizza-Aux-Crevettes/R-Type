/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Health.hpp
*/

#pragma once

#include "util/Config.hpp"

class Health {
  public:
    Health(double health = DEFAULT_HEALTH, double lives = DEFAULT_LIVES);

    double getHealth() const;
    double getLives() const;

    void takeDamage(double damage);
    void loseLife();
    bool isAlive() const;

  private:
    double _health;
    double _lives;
};
