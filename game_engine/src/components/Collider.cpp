/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Collider.cpp
**
** The Collider class represents the collider component for an entity in the
*game.
** It holds the size of the collider as a vector of doubles. The constructor
*allows initializing
** the size with a given vector of values.
*/

#include "components/Collider.hpp"

Collider::Collider(std::vector<double> size) : _size(size) {}

Collider::~Collider() {}

std::vector<double> Collider::getCollider() const {
    return this->_size;
}

void Collider::setCollider(std::vector<double> size) {
    this->_size = size;
}
