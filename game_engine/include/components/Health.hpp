/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Health.hpp
*/

#ifndef HEALTH_HPP_
#define HEALTH_HPP_
#include "Components.hpp"

class Health : public Component {
  public:
    Health(int initialHp = 100);
    ~Health();
    int getCurrentHp() const;
    void setCurrentHp(int currentHp);
    int getMaxHp() const;
    void setMaxHp(int maxHp);
    void display() const override;

  protected:
  private:
    int _currentHp;
    int _maxHp;
};

#endif /* !HEALTH_HPP_ */
