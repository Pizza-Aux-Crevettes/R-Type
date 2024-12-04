/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Bullet.hpp
*/

#pragma once

#include "../Entity.hpp"

class Bullet {
  public:
    Bullet(int damage = 0);
    ~Bullet();
    int getDamage() const;
    void setDamage(int damage);

  private:
    int _damage;
    Entity _sourceEntity;
};
