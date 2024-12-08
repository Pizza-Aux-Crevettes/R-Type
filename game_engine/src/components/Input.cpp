/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Input.cpp
**
** The Input class represents the input controls for a game entity.
** It holds boolean values for each control, including movement directions (up,
*right, left, down),
** attack state, and auto fire state. The constructor allows initializing these
*values with default values.
*/

#include "components/Input.hpp"
#include <iostream>

/**
 * @brief Constructor for the Input component.
 *
 * This constructor initializes the Input component with the given boolean values for the input actions.
 *
 * @param up Boolean indicating if the "up" action is active.
 * @param right Boolean indicating if the "right" action is active.
 * @param left Boolean indicating if the "left" action is active.
 * @param down Boolean indicating if the "down" action is active.
 * @param attack Boolean indicating if the "attack" action is active.
 * @param autoFire Boolean indicating if the "autoFire" action is active.
 */
Input::Input(bool up, bool right, bool left, bool down, bool attack,
             bool autoFire)
    : _up(up), _right(right), _left(left), _down(down), _attack(attack),
      _autoFire(autoFire) {}

/**
 * @brief Destructor for the Input component.
 *
 * This destructor cleans up any resources used by the Input component.
 */
Input::~Input() {}

/**
 * @brief Get the "up" action state of the Input component.
 *
 * This function retrieves whether the "up" action is active.
 *
 * @return `true` if the "up" action is active, `false` otherwise.
 */
bool Input::getUp() const {
    return this->_up;
}

/**
 * @brief Set the "up" action state of the Input component.
 *
 * This function sets the state of the "up" action.
 *
 * @param up A boolean indicating if the "up" action is active.
 */
void Input::setUp(bool up) {
    this->_up = up;
}

/**
 * @brief Get the "right" action state of the Input component.
 *
 * This function retrieves whether the "right" action is active.
 *
 * @return `true` if the "right" action is active, `false` otherwise.
 */
bool Input::getRight() const {
    return this->_right;
}

/**
 * @brief Set the "right" action state of the Input component.
 *
 * This function sets the state of the "right" action.
 *
 * @param right A boolean indicating if the "right" action is active.
 */
void Input::setRight(bool right) {
    this->_right = right;
}

/**
 * @brief Get the "left" action state of the Input component.
 *
 * This function retrieves whether the "left" action is active.
 *
 * @return `true` if the "left" action is active, `false` otherwise.
 */
bool Input::getLeft() const {
    return this->_left;
}

/**
 * @brief Set the "left" action state of the Input component.
 *
 * This function sets the state of the "left" action.
 *
 * @param left A boolean indicating if the "left" action is active.
 */
void Input::setLeft(bool left) {
    this->_left = left;
}

/**
 * @brief Get the "down" action state of the Input component.
 *
 * This function retrieves whether the "down" action is active.
 *
 * @return `true` if the "down" action is active, `false` otherwise.
 */
bool Input::getDown() const {
    return this->_down;
}

/**
 * @brief Set the "down" action state of the Input component.
 *
 * This function sets the state of the "down" action.
 *
 * @param down A boolean indicating if the "down" action is active.
 */
void Input::setDown(bool down) {
    this->_down = down;
}

/**
 * @brief Get the "attack" action state of the Input component.
 *
 * This function retrieves whether the "attack" action is active.
 *
 * @return `true` if the "attack" action is active, `false` otherwise.
 */
bool Input::getAttack() const {
    return this->_attack;
}

/**
 * @brief Set the "attack" action state of the Input component.
 *
 * This function sets the state of the "attack" action.
 *
 * @param attack A boolean indicating if the "attack" action is active.
 */
void Input::setAttack(bool attack) {
    this->_attack = attack;
}

/**
 * @brief Get the "autoFire" action state of the Input component.
 *
 * This function retrieves whether the "autoFire" action is active.
 *
 * @return `true` if the "autoFire" action is active, `false` otherwise.
 */
bool Input::getAutoFire() const {
    return this->_autoFire;
}

/**
 * @brief Set the "autoFire" action state of the Input component.
 *
 * This function sets the state of the "autoFire" action.
 *
 * @param autoFire A boolean indicating if the "autoFire" action is active.
 */
void Input::setAutoFire(bool autoFire) {
    this->_autoFire = autoFire;
}

/**
 * @brief Display the Input component information.
 *
 * This function displays a message indicating that the Input component is being displayed.
 */
void Input::display() const {
    std::cout << "Input component displayed!" << std::endl;
}