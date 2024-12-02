/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Bullet.cpp
**
** The Bullet class represents a bullet in the game, which has a certain damage value.
** The constructor allows initializing the damage value with default value.
*/

#include "components/Bullet.hpp"

Bullet::Bullet(int damage) : _damage(damage)
{
}

Bullet::~Bullet()
{
}

int Bullet::getDamage() const
{
    return this->_damage;
}

void Bullet::setDamage(int damage)
{
    this->_damage = damage;
}
