/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Player.hpp
*/

#pragma once

#include <memory>
#include <optional>
#include <string>
#include "util/Config.hpp"
#include "util/Point.hpp"

class Player {
  public:
    Player(const std::string& name, const Point& position,
           int16_t health = DEFAULT_HEALTH);

    int32_t getId() const;
    const std::string& getName() const;
    const Point& getPosition() const;
    void setPosition(const Point& position);
    std::optional<int> getClientSocket() const;
    void setClientSocket(int clientSocket);
    void takeDamage(int16_t damage);
    int16_t getHealth() const;
    void setHealth(int16_t health);
    int16_t getMaxHealth() const;

  private:
    int32_t _id;
    std::string _name;
    Point _position;
    Point _size;
    int16_t _speed;
    int16_t _health;
    std::optional<int> _clientSocket;
};
