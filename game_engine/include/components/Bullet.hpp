/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Bullet.hpp
*/

#ifndef BULLET_HPP_
#define BULLET_HPP_

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

#endif /* BULLET_HPP_ */
