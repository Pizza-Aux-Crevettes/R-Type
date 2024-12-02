#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Bullet.hpp"
#include "Health.hpp"
#include "Inventory.hpp"
#include "Point.hpp"
#include <string>
#include <vector>

class Player {
  private:
    std::string name;
    Point position;
    Point size;
    double speed;
    Health health;
    Inventory inventory;
    std::vector<Bullet> bulletList;

  public:
    std::string getName() const;
    void setName(const std::string& name);

    Point getPosition() const;
    void setPosition(const Point pos);

    Point getSize() const;
    void setSize(const Point& size);

    double getSpeed() const;
    void setSpeed(double speed);

    Health getHealth() const;
    void setHealth(const Health& health);

    Inventory getInventory() const;
    void setInventory(const Inventory& inventory);
};

#endif // PLAYER_HPP
