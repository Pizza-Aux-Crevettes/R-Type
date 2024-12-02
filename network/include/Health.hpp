/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Health.hpp
*/

#ifndef HEALTH_HPP
#define HEALTH_HPP

class Health {
private:
    double health;
    double lives;

public:
    double getHealth() const;
    void setHealth(double health);

    double getLives() const;
    void setLives(double lives);

    void reset();

    bool isDead() const;
    bool isGameOver() const;
};

#endif // HEALTH_HPP
