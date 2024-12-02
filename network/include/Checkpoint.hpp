/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Checkpoint.hpp
*/

#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP

#include "Point.hpp"

class Checkpoint {
  private:
    Point position;

  public:
    Point getPosition() const;
    void setPosition(const Point pos);
};

#endif // CHECKPOINT_HPP
