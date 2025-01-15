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
#include "util/Point.hpp"

class Player {
  public:
    Player(const std::string& name, const Point& position);

    int32_t getId() const;
    const std::string& getName() const;
    const Point& getPosition() const;
    void setPosition(const Point& position);
    std::optional<int> getClientSocket() const;
    void setClientSocket(int clientSocket);

  private:
    int32_t _id;
    std::string _name;
    Point _position;
    Point _size;
    double _speed;
    std::optional<int> _clientSocket;
};
