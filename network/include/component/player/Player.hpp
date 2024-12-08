/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Player.hpp
*/

#pragma once

#include "component/attr/Health.hpp"
#include "util/Point.hpp"
#include <string>

class Player {
  public:
    Player(const std::string& name, const Point& position = Point(),
           const Point& size = Point(), double speed = 0);

    void setPosition(const Point& position);
    const Point& getPosition() const;

    const std::string& getName() const;
    const Point& getSize() const;
    double getSpeed() const;
    const Health& getHealth() const;

    void move(double deltaX, double deltaY);

  private:
    std::string _name;
    Point _position;
    Point _size;
    double _speed;
    Health _health;
};
