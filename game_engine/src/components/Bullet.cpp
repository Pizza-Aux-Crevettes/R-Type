/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Bullet.cpp
**
** The Bullet class represents a bullet in the game, which has a certain damage
*value.
** The constructor allows initializing the damage value with default value.
*/

#include "components/Bullet.hpp"
#include <iostream>

/**
 * @brief Constructor for the Bullet component.
 *
 * This constructor initializes the Bullet component with the specified damage
 * value.
 *
 * @param damage The damage value of the bullet.
 */
Bullet::Bullet(int damage) : _damage(damage) {}

/**
 * @brief Destructor for the Bullet component.
 *
 * This destructor cleans up any resources used by the Bullet component.
 */
Bullet::~Bullet() {}

/**
 * @brief Get the damage of the Bullet component.
 *
 * This function retrieves the damage value of the bullet.
 *
 * @return The damage value of the bullet.
 */
int Bullet::getDamage() const {
    return this->_damage;
}

/**
 * @brief Set the damage of the Bullet component.
 *
 * This function sets the damage value of the bullet.
 *
 * @param damage The new damage value to be set for the bullet.
 */
void Bullet::setDamage(int damage) {
    this->_damage = damage;
}

/**
 * @brief Display the Bullet component information.
 *
 * This function displays a message indicating that the Bullet component is
 * being displayed.
 */
void Bullet::display() const {
    std::cout << "Bullet component displayed!" << std::endl;
}