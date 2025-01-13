/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Bullet.hpp
*/

#pragma once

#include "util/Point.hpp"

class Bullet {
  public:
    Bullet(const Point& position, const Point& direction, double speed);

    int getId() const;
    const Point& getPosition() const;
    void move();
    bool isOutsideViewport(int viewportWidth, int viewportHeight) const;

  private:
    int _id;
    Point _position;
    Point _direction;
    double _speed;
};
