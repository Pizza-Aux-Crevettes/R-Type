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

enum class EnemyType { NONE, ENEMY1, ENEMY2, ENEMY3, ENEMY4 };

class Enemy {
  public:
    Enemy(EnemyType type, const Point& position, double speed,
          double bulletSpeed, int width, int height, int shootCooldown,
          int shootRange);

    int32_t getId() const;
    EnemyType getType() const;
    void setType(EnemyType type);
    const Point& getPosition() const;
    void setPosition(const Point& position);
    double getSpeed() const;
    void setSpeed(double speed);
    double getBulletSpeed() const;
    void setBulletSpeed(double bulletSpeed);
    int getWidth() const;
    void setWidth(int width);
    int getHeight() const;
    void setHeight(int height);
    int getShootCooldown() const;
    void setShootCooldown(int shootCooldown);
    int getShootRange() const;
    void setShootRange(int shootRange);
    bool contains(int32_t x, int32_t y) const;
    bool collidesWith(const std::shared_ptr<Player>& player) const;
    bool canShoot() const;
    void resetShootCooldown();
    void move();

  private:
    int32_t _id;
    EnemyType _type;
    Point _position;
    double _speed;
    double _bulletSpeed;
    int _width;
    int _height;
    int _shootCooldown;
    int _shootRange;
    int _currentCooldown;
};
