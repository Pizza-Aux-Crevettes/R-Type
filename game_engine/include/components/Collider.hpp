/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Collider.hpp
*/

#pragma once

#include "Components.hpp"
#include <vector>

class Collider : public Component {
  public:
    Collider(std::pair<double, double> size = {0.0, 0.0});
    ~Collider();
    std::pair<double, double> getCollider() const;
    void setCollider(std::pair<double, double> size);
    void display() const override;

  private:
    std::pair<double, double> _size;
    sf::Rect<int> _rect;
    bool _isLoad = false;
};
