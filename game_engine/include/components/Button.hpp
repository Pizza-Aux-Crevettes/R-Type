/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Button.hpp
*/

#pragma once

#include "Components.hpp"
#include <string>

class Button : public Component {
  public:
    Button(std::string text = "", std::pair<double, double> size = {0.0, 0.0});
    ~Button();
    std::string getText() const;
    void setText(std::string text);
    std::pair<double, double> getSize() const;
    void setSize(std::pair<double, double> size);
    void display() const override;
    void createButton();

  private:
    std::string _text;
    std::pair<double, double> _size;
    enum Shape { Circle, Rectangle };
    sf::RectangleShape _button;
    bool _isLoad = false;
};
