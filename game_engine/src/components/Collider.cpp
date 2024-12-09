/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Collider.cpp
**
** The Collider class represents the collider component for an entity in the
** game.
** It holds the size of the collider as a pair of doubles. The constructor
** allows initializing
** the size with a given vector of values.
*/

#include "components/Collider.hpp"
#include <iostream>

/**
 * @brief Constructor for the Collider component.
 *
 * This constructor initializes the Collider component with a given size.
 * The size is represented as a pair of doubles (width, height).
 *
 * @param size A pair of doubles representing the size of the collider (width,
 * height).
 */
Collider::Collider(std::pair<double, double> size) : _size(size) {}

/**
 * @brief Destructor for the Collider component.
 *
 * This destructor cleans up any resources used by the Collider component.
 */
Collider::~Collider() {}

/**
 * @brief Get the size of the Collider component.
 *
 * This function retrieves the size of the collider as a pair of doubles.
 *
 * @return A pair of doubles representing the size of the collider (width,
 * height).
 */
std::pair<double, double> Collider::getCollider() const {
    return this->_size;
}

/**
 * @brief Set the size of the Collider component.
 *
 * This function sets the size of the collider as a pair of doubles.
 *
 * @param size A pair of doubles representing the new size of the collider
 * (width, height).
 */
void Collider::setCollider(std::pair<double, double> size) {
    this->_size = size;
}

/**
 * @brief Display the Collider component information.
 *
 * This function displays a message indicating that the Collider component is
 * being displayed.
 */
void Collider::display() const {
    std::cout << "Collider component displayed!" << std::endl;
}