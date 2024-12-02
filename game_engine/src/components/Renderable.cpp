/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Renderable.cpp
**
** The Renderable class represents an object that can be rendered in the game.
** It holds a boolean `isVisible` to indicate if the object is visible or not.
** The constructor allows initializing the visibility, with a default value of
*true.
*/

#include "components/Renderable.hpp"

Renderable::Renderable(bool isVisible) : _isVisible(isVisible) {}

Renderable::~Renderable() {}

bool Renderable::getIsVisible() const {
    return this->_isVisible;
}

void Renderable::setIsVisible(bool isVisible) {
    this->_isVisible = isVisible;
}
