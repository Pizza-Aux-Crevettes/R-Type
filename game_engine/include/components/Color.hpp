/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Color.hpp
*/

#pragma once

#include <vector>

class Color {
  public:
    Color(std::vector<double> color = {0.0, 0.0, 0.0});
    ~Color();
    std::vector<double> getColor() const;
    void setColor(std::vector<double> color);

  private:
    std::vector<double> _color;
};
