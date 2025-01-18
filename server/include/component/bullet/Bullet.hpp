/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Bullet.hpp
*/

#pragma once

#include <cstdint>
#include <memory>
#include "component/player/Player.hpp"
#include "util/Point.hpp"

enum class BulletType { PLAYER, ENEMY };

class Bullet {
  public:
    Bullet(const Point& position, const Point& direction, int16_t speed,
           BulletType type, int16_t damage,
           const std::shared_ptr<Player> player = nullptr);

    int32_t getId() const;
    const Point& getPosition() const;
    BulletType getType() const;
    int16_t getDamage() const;
    const std::shared_ptr<Player> getPlayer() const;
    void move();
    bool collidesWith(int32_t x, int32_t y, int32_t width,
                      int32_t height) const;

  private:
    int32_t _id;
    Point _position;
    Point _direction;
    int16_t _speed;
    BulletType _type;
    int16_t _damage;
    const std::shared_ptr<Player> _player;
};
