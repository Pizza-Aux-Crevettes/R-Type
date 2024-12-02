/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Enemy.hpp
*/

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Point.hpp"
#include "Health.hpp"
#include <vector>

class Enemy {
private:
    int id;
    Point position;
    Point size;
    std::vector<double> moveVector;
    Health health;

public:
    int getId() const;
    void setId(int id);

    Point getPosition() const;
    void setPosition(const Point pos);

    Point getSize() const;
    void setSize(const Point &size);

    std::vector<double> getMoveVector() const;
    void setMoveVector(const std::vector<double> vector);

    Health getHealth() const;
    void setHealth(const Health &health);
};

#endif // ENEMY_HPP
