/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Bullet.cpp
*/

#include "component/bullet/Bullet.hpp"
#include "component/attr/IDManager.hpp"
#include "util/Config.hpp"

/**
 * @brief Construct a new Bullet object
 *
 * @param position Initial position of the bullet
 * @param direction Direction vector (normalized)
 * @param speed Speed of the bullet
 */
Bullet::Bullet(const Point& position, const Point& direction, int16_t speed, BulletType type)
    : _id(IDManager::getNextId()), _position(position), _direction(direction),
      _speed(speed), _type(type) {}

/**
 * @brief Get the ID of the bullet
 *
 * @return int32_t The bullet ID
 */
int32_t Bullet::getId() const {
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

/**
 * @brief Check if the bullet collides with an entity
 *
 * @param x X position of the entity
 * @param y Y position of the entity
 * @param width Width of the entity
 * @param height Height of the entity
 * @return true If the bullet collides with the entity
 * @return false If the bullet does not collide with the entity
 */
bool Bullet::collidesWith(int32_t x, int32_t y, int32_t width, int32_t height) const {
    int32_t bulletX = _position.getX();
    int32_t bulletY = _position.getY();
    return !(bulletX + BULLET_WIDTH < x || bulletX > x + width || 
             bulletY + BULLET_HEIGHT < y || bulletY > y + height);
}

/**
 * @brief Get the type of the bullet
 *
 * @return BulletType The type of the bullet
 */
BulletType Bullet::getType() const {
    return _type;
}
