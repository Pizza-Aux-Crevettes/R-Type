/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Obstacle.hpp
*/

#pragma once

enum class ObstacleType { NONE = 0, BLOCK = 1 };

struct Obstacle {
    ObstacleType _type;
    int _x;
    int _y;

    Obstacle(ObstacleType type, int x, int y) : _type(type), _x(x), _y(y) {}
};
