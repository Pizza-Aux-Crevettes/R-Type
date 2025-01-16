/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Enemy.cpp
*/

#include "component/enemy/Enemy.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"

/**
 * @brief Construct a new Enemy object
 *
 * @param type The type of the enemy
 * @param position The position of the enemy
 * @param speed The speed of the enemy
 * @param width The width of the enemy
 * @param height The height of the enemy
 * @param bulletSpeed The speed of the enemy's bullets
 * @param bulletDamage The damage of the enemy's bullets
 * @param shootCooldown The cooldown between shots
 * @param shootRange The range at which the enemy can shoot
 */
Enemy::Enemy(EnemyType type, const Point& position, int16_t speed,
             int16_t width, int16_t height, int16_t bulletSpeed,
             int16_t bulletDamage, int16_t shootCooldown, int16_t shootRange)
    : _id(IDManager::getNextId()), _type(type), _position(position),
      _speed(speed), _width(width), _height(height), _bulletSpeed(bulletSpeed),
      _bulletDamage(bulletDamage), _shootCooldown(shootCooldown),
      _shootRange(shootRange), _currentCooldown(0) {}

/**
 * @brief Get the ID of the enemy
 *
 * @return int32_t The ID of the enemy
 */
int32_t Enemy::getId() const {
    return _id;
}

/**
 * @brief Get the type of the enemy
 *
 * @return EnemyType The type of the enemy
 */
EnemyType Enemy::getType() const {
    return _type;
}

/**
 * @brief Get the position of the enemy
 *
 * @return const Point& The position of the enemy
 */
const Point& Enemy::getPosition() const {
    return _position;
}

/**
 * @brief Get the speed of the enemy
 *
 * @return int16_t The speed of the enemy
 */
int16_t Enemy::getSpeed() const {
    return _speed;
}

/**
 * @brief Get the speed of the enemy's bullets
 *
 * @return int16_t The speed of the enemy's bullets
 */
int16_t Enemy::getBulletSpeed() const {
    return _bulletSpeed;
}

/**
 * @brief Get the speed of the enemy's bullets
 *
 * @return int16_t The speed of the enemy's bullets
 */
int16_t Enemy::getBulletDamage() const {
    return _bulletDamage;
}

/**
 * @brief Get the width of the enemy
 *
 * @return int16_t The width of the enemy
 */
int16_t Enemy::getWidth() const {
    return _width;
}

/**
 * @brief Get the height of the enemy
 *
 * @return int16_t The height of the enemy
 */
int16_t Enemy::getHeight() const {
    return _height;
}

/**
 * @brief Get the shoot cooldown of the enemy
 *
 * @return int16_t The shoot cooldown of the enemy
 */
int16_t Enemy::getShootCooldown() const {
    return _shootCooldown;
}

/**
 * @brief Get the shoot range of the enemy
 *
 * @return int16_t The shoot range of the enemy
 */
int16_t Enemy::getShootRange() const {
    return _shootRange;
}

/**
 * @brief Get the enemy's health
 *
 * @return int16_t The enemy's health
 */
int16_t Enemy::getHealth() const {
    return _health;
}

/**
 * @brief Set the enemy's health
 *
 * @param health The enemy's health
 */
void Enemy::setHealth(int16_t health) {
    _health = health;
}

/**
 * @brief Check if the enemy contains a point
 *
 * @param x The x coordinate
 * @param y The y coordinate
 * @return true If the point is within the enemy's bounds
 * @return false Otherwise
 */
bool Enemy::contains(int32_t x, int32_t y) const {
    return x >= _position.getX() && x < _position.getX() + OBSTACLE_SIZE &&
           y >= _position.getY() && y < _position.getY() + OBSTACLE_SIZE;
}

/**
 * @brief Check if the enemy collides with a player
 *
 * @param player The player to check
 * @return true If the enemy collides with the player
 * @return false Otherwise
 */
bool Enemy::collidesWith(const std::shared_ptr<Player>& player) const {
    int32_t playerX = player->getPosition().getX();
    int32_t playerY = player->getPosition().getY();

    return contains(playerX, playerY) ||
           contains(playerX + PLAYER_WIDTH, playerY) ||
           contains(playerX, playerY + PLAYER_HEIGHT) ||
           contains(playerX + PLAYER_WIDTH, playerY + PLAYER_HEIGHT);
}

/**
 * @brief Check if the enemy can shoot
 *
 * @return true If the enemy can shoot
 * @return false Otherwise
 */
bool Enemy::canShoot() const {
    return _currentCooldown <= 0;
}

/**
 * @brief Reset the shoot cooldown
 *
 */
void Enemy::resetShootCooldown() {
    _currentCooldown = _shootCooldown;
}

/**
 * @brief Update the shoot cooldown
 *
 */
void Enemy::updateShootCooldown() {
    _currentCooldown -= CADENCY;
}

/**
 * @brief Move the enemy
 *
 */
void Enemy::move() {
    _position.setX(_position.getX() - _speed);
}

/**
 * @brief Take damage
 *
 * @param damage The amount of damage to take
 */
void Enemy::takeDamage(int16_t damage) {
    _health -= damage;
    if (_health <= 0) {
        Logger::info("[Enemy] Enemy " + std::to_string(_id) + " died.");
    }
}
