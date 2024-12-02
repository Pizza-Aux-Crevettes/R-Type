/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Rigidbody.cpp
**
** The Rigidbody class represents the physical properties of an object,
** such as mass, drag, gravity scale, and forces applied to it.
** It provides getters and setters to manipulate these properties.
*/

#include "components/Rigidbody.hpp"

Rigidbody::Rigidbody(float mass, float drag, float gravityScale, float forceX,
                     float forceY)
    : _mass(mass), _drag(drag), _gravityScale(gravityScale), _forceX(forceX),
      _forceY(forceY) {}

Rigidbody::~Rigidbody() {}

float Rigidbody::getMass() const {
    return this->_mass;
}

void Rigidbody::setMass(float mass) {
    this->_mass = mass;
}

float Rigidbody::getDrag() const {
    return this->_drag;
}

void Rigidbody::setDrag(float drag) {
    this->_drag = drag;
}

float Rigidbody::getGravityScale() const {
    return this->_gravityScale;
}

void Rigidbody::setGravityScale(float gravityScale) {
    this->_gravityScale = gravityScale;
}

float Rigidbody::getForceX() const {
    return this->_forceX;
}

void Rigidbody::setForceX(float forceX) {
    this->_forceX = forceX;
}

float Rigidbody::getForceY() const {
    return this->_forceY;
}

void Rigidbody::setForceY(float forceY) {
    this->_forceY = forceY;
}
