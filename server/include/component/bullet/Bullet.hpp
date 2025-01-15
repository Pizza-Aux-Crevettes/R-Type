/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Bullet.hpp
*/

#pragma once

#include "util/Point.hpp"
#include <cstdint>

class Bullet {
  public:
    Bullet(const Point& position, const Point& direction, int16_t speed);

    int32_t getId() const;
    const Point& getPosition() const;
    void move();

  private:
    int32_t _id;
    Point _position;
    Point _direction;
    int16_t _speed;
};
