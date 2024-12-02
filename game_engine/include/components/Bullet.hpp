/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Bullet.hpp
*/

#ifndef BULLET_HPP_
#define BULLET_HPP_

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

#endif /* BULLET_HPP_ */
