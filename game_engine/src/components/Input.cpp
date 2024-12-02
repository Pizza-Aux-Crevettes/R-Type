/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Input.cpp
**
** The Input class represents the input controls for a game entity.
** It holds boolean values for each control, including movement directions (up, right, left, down), 
** attack state, and auto fire state. The constructor allows initializing these values with default values.
*/

#include "components/Input.hpp"

Input::Input(bool up, bool right, bool left, bool down, bool attack, bool autoFire) : _up(up), _right(right), _left(left), _down(down), _attack(attack), _autoFire(autoFire)
{
}

Input::~Input()
{
}

bool Input::getUp() const
{
    return this->_up;
}

void Input::setUp(bool up)
{
    this->_up = up;
}

bool Input::getRight() const
{
    return this->_right;
}

void Input::setRight(bool right)
{
    this->_right = right;
}

bool Input::getLeft() const
{
    return this->_left;
}

void Input::setLeft(bool left)
{
    this->_left = left;
}

bool Input::getDown() const
{
    return this->_down;
}

void Input::setDown(bool down)
{
    this->_down = down;
}

bool Input::getAttack() const
{
    return this->_attack;
}

void Input::setAttack(bool attack)
{
    this->_attack = attack;
}

bool Input::getAutoFire() const
{
    return this->_autoFire;
}

void Input::setAutoFire(bool autoFire)
{
    this->_autoFire = autoFire;
}
