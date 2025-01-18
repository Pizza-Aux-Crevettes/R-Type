/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Player.hpp
*/

#pragma once

#include <memory>
#include <netinet/in.h>
#include <optional>
#include <string>
#include "util/Config.hpp"
#include "util/Point.hpp"

class Player {
  public:
    Player(const std::string& name, const Point& position,
           int16_t health = DEFAULT_HEALTH, bool isAlive = true,
           int16_t kills = 0, int32_t score = 0);

    int32_t getId() const;
    const std::string& getName() const;
    const Point& getPosition() const;
    void setPosition(const Point& position);
    std::optional<int> getClientSocket() const;
    void setClientSocket(int clientSocket);
    std::optional<sockaddr_in> getClientAddr() const;
    void setClientAddr(const sockaddr_in& clientAddr);
    int16_t getHealth() const;
    void setHealth(int16_t health);
    int16_t getMaxHealth() const;
    bool isAlive() const;
    void takeDamage(int16_t damage);
    int16_t getKills() const;
    void addKill();
    int32_t getScore() const;
    void addScore(int32_t score);

  private:
    int32_t _id;
    std::string _name;
    Point _position;
    Point _size;
    int16_t _speed;
    int16_t _health;
    bool _isAlive;
    int16_t _kills;
    int32_t _score;
    std::optional<sockaddr_in> _clientAddr;
    std::optional<int> _clientSocket;
};
