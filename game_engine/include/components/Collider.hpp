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
    Collider(std::vector<double> size = {0.0, 0.0});
    ~Collider();
    std::vector<double> getCollider() const;
    void setCollider(std::vector<double> size);

  private:
    std::vector<double> _size;
};

#endif /* COLLIDER_HPP_ */
