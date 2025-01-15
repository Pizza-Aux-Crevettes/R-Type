/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Obstacle.hpp
*/

#pragma once

#include <string>
#include "component/player/Player.hpp"
#include "util/Point.hpp"

enum class ObstacleType {
    NONE,
    BLOCK,
    BLOCK2,
    BLOCK3,
    BLOCK4,
};

class Obstacle {
  public:
    Obstacle(ObstacleType type, const Point& position);

    int32_t getId() const;
    ObstacleType getType() const;
    void setType(ObstacleType type);
    const Point& getPosition() const;
    void setPosition(const Point& position);
    bool contains(int32_t x, int32_t y) const;
    bool collidesWith(const std::shared_ptr<Player>& player) const;

  private:
    int32_t _id;
    ObstacleType _type;
    Point _position;
};
