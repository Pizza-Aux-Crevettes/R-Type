/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Enemy.cpp
*/

#include "component/enemy/Enemy.hpp"
#include "util/Config.hpp"

/**
 * @brief Construct a new Enemy object
 *
 * @param type The type of the enemy
 * @param position The position of the enemy
 * @param speed The speed of the enemy
 * @param bulletSpeed The speed of the enemy's bullets
 * @param width The width of the enemy
 * @param height The height of the enemy
 * @param shootCooldown The cooldown between shots
 * @param shootRange The range at which the enemy can shoot
 */
Enemy::Enemy(EnemyType type, const Point& position, double speed,
             double bulletSpeed, int width, int height, int shootCooldown,
             int shootRange)
    : _id(IDManager::getNextId()), _type(type), _position(position),
      _speed(speed), _bulletSpeed(bulletSpeed), _width(width), _height(height),
      _shootCooldown(shootCooldown), _shootRange(shootRange),
      _currentCooldown(0) {}

/**
 * @brief Get the ID of the enemy
 *
 * @return int The ID of the enemy
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
 * @brief Set the type of the enemy
 *
 * @param type The type of the enemy
 */
void Enemy::setType(EnemyType type) {
    _type = type;
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
 * @brief Set the position of the enemy
 *
 * @param position The position of the enemy
 */
void Enemy::setPosition(const Point& position) {
    _position = position;
}

/**
 * @brief Get the speed of the enemy
 *
 * @return double The speed of the enemy
 */
double Enemy::getSpeed() const {
    return _speed;
}

/**
 * @brief Set the speed of the enemy
 *
 * @param speed The speed of the enemy
 */
void Enemy::setSpeed(double speed) {
    _speed = speed;
}

/**
 * @brief Get the speed of the enemy's bullets
 *
 * @return double The speed of the enemy's bullets
 */
double Enemy::getBulletSpeed() const {
    return _bulletSpeed;
}

/**
 * @brief Set the speed of the enemy's bullets
 *
 * @param bulletSpeed The speed of the enemy's bullets
 */
void Enemy::setBulletSpeed(double bulletSpeed) {
    _bulletSpeed = bulletSpeed;
}

/**
 * @brief Get the width of the enemy
 *
 * @return int The width of the enemy
 */
int Enemy::getWidth() const {
    return _width;
}

/**
 * @brief Set the width of the enemy
 *
 * @param width The width of the enemy
 */
void Enemy::setWidth(int width) {
    _width = width;
}

/**
 * @brief Get the height of the enemy
 *
 * @return int The height of the enemy
 */
int Enemy::getHeight() const {
    return _height;
}

/**
 * @brief Set the height of the enemy
 *
 * @param height The height of the enemy
 */
void Enemy::setHeight(int height) {
    _height = height;
}

/**
 * @brief Get the shoot cooldown of the enemy
 *
 * @return int The shoot cooldown of the enemy
 */
int Enemy::getShootCooldown() const {
    return _shootCooldown;
}

/**
 * @brief Set the shoot cooldown of the enemy
 *
 * @param shootCooldown The shoot cooldown of the enemy
 */
void Enemy::setShootCooldown(int shootCooldown) {
    _shootCooldown = shootCooldown;
}

/**
 * @brief Get the shoot range of the enemy
 *
 * @return int The shoot range of the enemy
 */
int Enemy::getShootRange() const {
    return _shootRange;
}

/**
 * @brief Set the shoot range of the enemy
 *
 * @param shootRange The shoot range of the enemy
 */
void Enemy::setShootRange(int shootRange) {
    _shootRange = shootRange;
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
 * @brief Move the enemy
 *
 */
void Enemy::move() {
    _position.setX(_position.getX() - _speed);
}
