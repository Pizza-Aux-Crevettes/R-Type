/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Renderable.hpp
*/

#pragma once

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
