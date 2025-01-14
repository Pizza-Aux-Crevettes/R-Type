/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Bullet.cpp
*/

#include "component/bullet/Bullet.hpp"
#include "component/attr/IDManager.hpp"

/**
 * @brief Construct a new Bullet object
 *
 * @param position Initial position of the bullet
 * @param direction Direction vector (normalized)
 * @param speed Speed of the bullet
 */
Bullet::Bullet(const Point& position, const Point& direction, double speed)
    : _id(IDManager::getNextId()), _position(position), _direction(direction),
      _speed(speed) {}

/**
 * @brief Get the ID of the bullet
 *
 * @return int The bullet ID
 */
int Bullet::getId() const {
    return _id;
}

/**
 * @brief Get the position of the bullet
 *
 * @return const Point& The position of the bullet
 */
const Point& Bullet::getPosition() const {
    return _position;
}

/**
 * @brief Move the bullet
 */
void Bullet::move() {
    _position.setX(_position.getX() + _direction.getX() * _speed);
    _position.setY(_position.getY() + _direction.getY() * _speed);
}
