/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Collider.hpp
*/

#ifndef COLLIDER_HPP_
#define COLLIDER_HPP_

#include <vector>

class Collider {
  public:
    Collider(std::pair<double, double> size = {0.0, 0.0});
    ~Collider();
    std::pair<double, double> getCollider() const;
    void setCollider(std::pair<double, double> size);

  private:
    std::pair<double, double> _size;
};

#endif /* COLLIDER_HPP_ */
