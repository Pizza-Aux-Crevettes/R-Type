/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Player.hpp
*/

#pragma once

#include <string>
#include "component/attr/Health.hpp"
#include "util/Point.hpp"

class Player {
  public:
    Player(const std::string& name, const Point& position, const Point& size,
           double speed);

    int32_t getId() const;
    const std::string& getName() const;
    const Point& getPosition() const;
    void setPosition(const Point& position);
    const Point& getSize() const;
    double getSpeed() const;
    const Health& getHealth() const;
    void move(double deltaX, double deltaY);

  private:
    int32_t _id;
    std::string _name;
    Point _position;
    Point _size;
    double _speed;
    Health _health;
};
