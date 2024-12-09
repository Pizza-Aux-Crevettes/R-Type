/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Bullet.hpp
*/

#pragma once

#include "Entity.hpp"

class Bullet : public Component {
  public:
    Bullet(int damage = 0);
    ~Bullet();
    int getDamage() const;
    void setDamage(int damage);
    void display() const override;

  private:
    int _damage;
};
