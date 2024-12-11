/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position.hpp
*/

#pragma once
#include "Components.hpp"

class Position : public Component {
  public:
    Position(std::pair<float, float> position = {0.0f, 0.0f});
    ~Position();
    float getPositionX() const;
    void setPositionX(float x);
    float getPositionY() const;
    void setPositionY(float y);
    void display() const override;

  private:
    float _x;
    float _y;
};
