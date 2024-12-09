/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Velocity.hpp
*/

#pragma once
#include "Components.hpp"

class Velocity : public Component {
  public:
    Velocity(float x = 0.0f, float y = 0.0f);
    ~Velocity();
    float getVelocityX() const;
    void setVelocityX(float x);
    float getVelocityY() const;
    void setVelocityY(float y);
    void display() const override;

  private:
    float _x;
    float _y;
};
