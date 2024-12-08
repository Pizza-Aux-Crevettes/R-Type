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
#include <iostream>

/**
 * @brief Constructor for the Rigidbody component.
 *
 * This constructor initializes the Rigidbody component with the given parameters for mass, drag,
 * gravity scale, and force in the X and Y directions.
 *
 * @param mass The mass of the rigidbody (usually in kg).
 * @param drag The drag coefficient of the rigidbody.
 * @param gravityScale A scale factor for gravity applied to the rigidbody.
 * @param forceX The force applied to the rigidbody in the X direction.
 * @param forceY The force applied to the rigidbody in the Y direction.
 */
Rigidbody::Rigidbody(float mass, float drag, float gravityScale, float forceX,
                     float forceY)
    : _mass(mass), _drag(drag), _gravityScale(gravityScale), _forceX(forceX),
      _forceY(forceY) {}

/**
 * @brief Destructor for the Rigidbody component.
 *
 * This destructor cleans up any resources used by the Rigidbody component.
 */
Rigidbody::~Rigidbody() {}

/**
 * @brief Get the mass of the Rigidbody.
 *
 * This function retrieves the mass of the rigidbody.
 *
 * @return The mass of the rigidbody.
 */
float Rigidbody::getMass() const {
    return this->_mass;
}

/**
 * @brief Set the mass of the Rigidbody.
 *
 * This function sets the mass of the rigidbody.
 *
 * @param mass The new mass of the rigidbody.
 */
void Rigidbody::setMass(float mass) {
    this->_mass = mass;
}

/**
 * @brief Get the drag coefficient of the Rigidbody.
 *
 * This function retrieves the drag coefficient of the rigidbody.
 *
 * @return The drag coefficient of the rigidbody.
 */
float Rigidbody::getDrag() const {
    return this->_drag;
}

/**
 * @brief Set the drag coefficient of the Rigidbody.
 *
 * This function sets the drag coefficient of the rigidbody.
 *
 * @param drag The new drag coefficient of the rigidbody.
 */
void Rigidbody::setDrag(float drag) {
    this->_drag = drag;
}

/**
 * @brief Get the gravity scale factor of the Rigidbody.
 *
 * This function retrieves the gravity scale factor of the rigidbody.
 *
 * @return The gravity scale factor of the rigidbody.
 */
float Rigidbody::getGravityScale() const {
    return this->_gravityScale;
}

/**
 * @brief Set the gravity scale factor of the Rigidbody.
 *
 * This function sets the gravity scale factor of the rigidbody.
 *
 * @param gravityScale The new gravity scale factor of the rigidbody.
 */
void Rigidbody::setGravityScale(float gravityScale) {
    this->_gravityScale = gravityScale;
}

/**
 * @brief Get the force applied to the Rigidbody in the X direction.
 *
 * This function retrieves the force applied to the rigidbody in the X direction.
 *
 * @return The force in the X direction.
 */
float Rigidbody::getForceX() const {
    return this->_forceX;
}

/**
 * @brief Set the force applied to the Rigidbody in the X direction.
 *
 * This function sets the force applied to the rigidbody in the X direction.
 *
 * @param forceX The new force to apply in the X direction.
 */
void Rigidbody::setForceX(float forceX) {
    this->_forceX = forceX;
}

/**
 * @brief Get the force applied to the Rigidbody in the Y direction.
 *
 * This function retrieves the force applied to the rigidbody in the Y direction.
 *
 * @return The force in the Y direction.
 */
float Rigidbody::getForceY() const {
    return this->_forceY;
}

/**
 * @brief Set the force applied to the Rigidbody in the Y direction.
 *
 * This function sets the force applied to the rigidbody in the Y direction.
 *
 * @param forceY The new force to apply in the Y direction.
 */
void Rigidbody::setForceY(float forceY) {
    this->_forceY = forceY;
}

/**
 * @brief Display the Rigidbody component information.
 *
 * This function displays a message indicating that the Rigidbody component is being displayed.
 */
void Rigidbody::display() const {
    std::cout << "Rigidbody component displayed!" << std::endl;
}