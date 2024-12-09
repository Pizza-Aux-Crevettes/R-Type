/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position.hpp
*/

#pragma once

class Position : public Component {
  public:
    Position(float x = 0.0f, float y = 0.0f);
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
