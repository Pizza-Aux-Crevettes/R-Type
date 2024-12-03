/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Click.hpp
*/

#pragma once

class Click {
  private:
    bool _up;
    bool _right;
    bool _left;
    bool _down;
    bool _attack;
    bool _autoFire;

  public:
    Click();
    ~Click();
    bool getUp();
    void setUp();
    bool getRight();
    void setRight();
    bool getLeft();
    void setLeft();
    bool getDown();
    void setDown();
    bool getAttack();
    void setAttack();
    bool getAutoFire();
    void setAutoFire();
};