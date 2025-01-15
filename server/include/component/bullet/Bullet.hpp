/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Bullet.hpp
*/

#pragma once

#include "util/Point.hpp"
#include <cstdint>

enum class BulletType { PLAYER, ENEMY };

class Bullet {
  public:
    Bullet(const Point& position, const Point& direction, int16_t speed, BulletType type);

    int32_t getId() const;
    const Point& getPosition() const;
    BulletType getType() const;
    void move();
    bool collidesWith(int32_t x, int32_t y, int32_t width, int32_t height) const;

  private:
    int32_t _id;
    Point _position;
    Point _direction;
    int16_t _speed;
    BulletType _type;
};
