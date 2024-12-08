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
#include <iostream>

/**
 * @brief Constructor for the Renderable component.
 *
 * This constructor initializes the Renderable component with the given
 * visibility state.
 *
 * @param isVisible A boolean indicating whether the component is visible or
 * not.
 */
Renderable::Renderable(bool isVisible) : _isVisible(isVisible) {}

/**
 * @brief Destructor for the Renderable component.
 *
 * This destructor cleans up any resources used by the Renderable component.
 */
Renderable::~Renderable() {}

/**
 * @brief Get the visibility state of the Renderable component.
 *
 * This function retrieves the visibility state of the component.
 *
 * @return `true` if the component is visible, `false` otherwise.
 */
bool Renderable::getIsVisible() const {
    return this->_isVisible;
}

/**
 * @brief Set the visibility state of the Renderable component.
 *
 * This function sets the visibility state of the component.
 *
 * @param isVisible A boolean indicating whether the component should be visible
 * or not.
 */
void Renderable::setIsVisible(bool isVisible) {
    this->_isVisible = isVisible;
}

/**
 * @brief Display the Renderable component information.
 *
 * This function displays a message indicating that the Renderable component is
 * being displayed.
 */
void Renderable::display() const {
    std::cout << "Renderable component displayed!" << std::endl;
}