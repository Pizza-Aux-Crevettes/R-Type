/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Player.hpp
*/

#pragma once

#include "component/attr/Health.hpp"
#include "util/Point.hpp"
#include <string>
#include <thread>

class Player {
  public:
    Player(int32_t userId, const std::string& name,
           const Point& position = Point(), const Point& size = Point(),
           double speed = 0);

    int32_t getId() const;
    const std::string& getName() const;
    const Point& getPosition() const;
    const Point& getSize() const;
    double getSpeed() const;
    const Health& getHealth() const;
    std::thread::id getThreadId() const;

    void setPosition(const Point& position);
    void setThreadId(const std::thread::id& threadId);

    void move(double deltaX, double deltaY);

  private:
    int32_t _userId;
    std::string _name;
    Point _position;
    Point _size;
    double _speed;
    Health _health;
    std::thread::id _threadId;
};
