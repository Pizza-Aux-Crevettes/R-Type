/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Renderable.hpp
*/

#pragma once

class Renderable {
  public:
    Renderable(bool isVisible = true);
    ~Renderable();
    bool getIsVisible() const;
    void setIsVisible(bool isVisible);

  private:
    bool _isVisible;
};
