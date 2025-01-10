/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Obstacle.hpp
*/

#pragma once

#include "util/Point.hpp"
#include <string>

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

    int getId() const;
    ObstacleType getType() const;
    void setType(ObstacleType type);
    const Point& getPosition() const;
    void setPosition(const Point& position);

  private:
    int _id;
    ObstacleType _type;
    Point _position;
};
