/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Health.hpp
*/

#pragma once

class Health {
  public:
    Health(int initialHp = 100);
    ~Health();
    int getCurrentHp() const;
    void setCurrentHp(int currentHp);
    int getMaxHp() const;
    void setMaxHp(int maxHp);

  protected:
  private:
    int _currentHp;
    int _maxHp;
};
