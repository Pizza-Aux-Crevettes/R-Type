/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Input.hpp
*/

#pragma once

class Input : public Component {
  public:
    Input(bool up = false, bool right = false, bool left = false,
          bool down = false, bool attack = false, bool autoFire = false);
    ~Input();
    bool getUp() const;
    void setUp(bool up);
    bool getRight() const;
    void setRight(bool right);
    bool getLeft() const;
    void setLeft(bool left);
    bool getDown() const;
    void setDown(bool down);
    bool getAttack() const;
    void setAttack(bool attack);
    bool getAutoFire() const;
    void setAutoFire(bool autoFire);
    void display() const override;

  private:
    bool _up;
    bool _right;
    bool _left;
    bool _down;
    bool _attack;
    bool _autoFire;
};
