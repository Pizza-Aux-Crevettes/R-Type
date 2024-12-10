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

    void setPosition(const Point& position);
    const Point& getPosition() const;

    std::thread::id getThreadId() const;
    void setThreadId(const std::thread::id& threadId);

    int32_t getId() const;
    const std::string& getName() const;
    const Point& getSize() const;
    double getSpeed() const;
    const Health& getHealth() const;

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
