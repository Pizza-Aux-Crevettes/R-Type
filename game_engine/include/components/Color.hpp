/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Color.hpp
*/

#pragma once

#include "Components.hpp"
#include <vector>

class Color : public Component {
  public:
    Color(std::vector<double> color = {0.0, 0.0, 0.0});
    ~Color();
    std::vector<double> getColor() const;
    void setColor(std::vector<double> color);
    void display() const override;

  private:
    std::vector<double> _color;
};
