/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Health.cpp
**
** The Health class represents the health system of an entity in the game.
** It tracks the current health (currentHp) and the maximum health (maxHp)
** of the entity. The constructor allows initializing the current health
** with a specified value, while the maximum health is fixed at 100.
*/

#include "components/Health.hpp"
#include <iostream>

/**
 * @brief Constructor for the Health component.
 *
 * This constructor initializes the Health component with the given initial
 * health points. The maximum health points are set to 100 by default.
 *
 * @param initialHp The initial value of the current health points.
 */
Health::Health(int initialHp) : _currentHp(initialHp), _maxHp(100) {}

/**
 * @brief Destructor for the Health component.
 *
 * This destructor cleans up any resources used by the Health component.
 */
Health::~Health() {}

/**
 * @brief Get the current health points of the Health component.
 *
 * This function retrieves the current health points of the entity.
 *
 * @return The current health points of the entity.
 */
int Health::getCurrentHp() const {
    return this->_currentHp;
}

/**
 * @brief Set the current health points of the Health component.
 *
 * This function sets the current health points for the entity.
 *
 * @param currentHp The new value for the current health points.
 */
void Health::setCurrentHp(int currentHp) {
    this->_currentHp = currentHp;
}

/**
 * @brief Get the maximum health points of the Health component.
 *
 * This function retrieves the maximum health points of the entity.
 *
 * @return The maximum health points of the entity.
 */
int Health::getMaxHp() const {
    return this->_maxHp;
}

/**
 * @brief Set the maximum health points of the Health component.
 *
 * This function sets the maximum health points for the entity.
 *
 * @param maxHp The new value for the maximum health points.
 */
void Health::setMaxHp(int maxHp) {
    this->_maxHp = maxHp;
}

/**
 * @brief Display the Health component information.
 *
 * This function displays a message indicating that the Health component is
 * being displayed.
 */
void Health::display() const {
    std::cout << "Health component displayed!" << std::endl;
}