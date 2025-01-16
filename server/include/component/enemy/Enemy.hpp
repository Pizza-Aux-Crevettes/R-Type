/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Enemy.hpp
*/

#pragma once

#include "component/attr/IDManager.hpp"
#include "component/player/Player.hpp"
#include "util/Config.hpp"
#include "util/Point.hpp"

enum class EnemyType {
    NONE,
    GRUNT,
    SNIPER,
    TANK,
    SWARMER,
    BOSS,
    DRONE,
    MINION,
    CANNON
};

class Enemy {
  public:
    Enemy(EnemyType type, const Point& position, int16_t speed, int16_t width,
          int16_t height, int16_t bulletSpeed, int16_t bulletDamage,
          int16_t shootCooldown, int16_t shootRange, int16_t health);

    int32_t getId() const;
    EnemyType getType() const;
    const Point& getPosition() const;
    int16_t getSpeed() const;
    int16_t getBulletSpeed() const;
    int16_t getBulletDamage() const;
    int16_t getWidth() const;
    int16_t getHeight() const;
    int16_t getShootCooldown() const;
    int16_t getShootRange() const;
    int16_t getHealth() const;
    int16_t getMaxHealth() const;
    void setHealth(int16_t health);
    bool contains(int32_t x, int32_t y) const;
    bool collidesWith(const std::shared_ptr<Player>& player) const;
    bool canShoot() const;
    void resetShootCooldown();
    void updateShootCooldown();
    void move();
    void takeDamage(int16_t damage);

  private:
    int32_t _id;
    EnemyType _type;
    Point _position;
    int16_t _speed;
    int16_t _width;
    int16_t _height;
    int16_t _bulletSpeed;
    int16_t _bulletDamage;
    int16_t _shootCooldown;
    int16_t _shootRange;
    int16_t _health;
    int16_t _maxHealth;
    int16_t _currentCooldown;
};
