/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Renderable.hpp
*/

#ifndef RENDERABLE_HPP_
#define RENDERABLE_HPP_
#include "Components.hpp"

class Renderable : public Component {
  public:
    Renderable(bool isVisible = true);
    ~Renderable();
    bool getIsVisible() const;
    void setIsVisible(bool isVisible);
    void display() const override;

  private:
    bool _isVisible;
};

#endif /* RENDERABLE_HPP_ */
