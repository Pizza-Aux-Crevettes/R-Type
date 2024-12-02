/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Bullet.hpp
*/

#ifndef BULLET_HPP
#define BULLET_HPP

#include "BulletType.hpp"
#include "Point.hpp"
#include <vector>

class Bullet {
  private:
    Point size;
    Point position;
    std::vector<double> moveVector;
    BulletType type;

  public:
    Point getSize() const;
    void setSize(const Point& size);

    Point getPosition() const;
    void setPosition(const Point pos);

    std::vector<double> getMoveVector() const;
    void setMoveVector(const std::vector<double> vector);

    BulletType getType() const;
    void setType(BulletType type);
};

#endif // BULLET_HPP
