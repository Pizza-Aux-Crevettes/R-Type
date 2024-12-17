/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Obstacle.hpp
*/

#pragma once

#include <string>
#include <utility>

#pragma once

enum class ObstacleType {
    NONE,
    ROCK,
    TREE,
    WALL
};

class Obstacle {
  public:
    Obstacle(ObstacleType type = ObstacleType::NONE, int16_t x = 0, int16_t y = 0, int16_t width = 0, int16_t height = 0, bool traversable = false);

    [[nodiscard]] ObstacleType getType() const;
    [[nodiscard]] int16_t getX() const;
    [[nodiscard]] int16_t getY() const;
    [[nodiscard]] int16_t getWidth() const;
    [[nodiscard]] int16_t getHeight() const;
    [[nodiscard]] bool isTraversable() const;

  private:
    ObstacleType _type;
    int16_t _x;
    int16_t _y;
    int16_t _width;
    int16_t _height;
    bool _traversable;
};
