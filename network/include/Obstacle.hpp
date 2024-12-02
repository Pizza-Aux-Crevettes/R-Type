/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Obstacle.hpp
*/

#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "Point.hpp"
#include "ObstacleType.hpp"

class Obstacle {
private:
    Point position;
    ObstacleType type;
    Point size;

public:
    Point getPosition() const;
    void setPosition(const Point pos);

    ObstacleType getType() const;
    void setType(ObstacleType);

    Point getSize() const;
    void setSize(const Point &size);
};

#endif // OBSTACLE_HPP
