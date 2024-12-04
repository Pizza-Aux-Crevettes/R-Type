/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Button.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button {
  public:
    Button(std::string text = "", std::pair<double, double> size = {0.0, 0.0});
    ~Button();
    std::string getText() const;
    void setText(std::string text);
    std::pair<double, double> getSize() const;
    void setSize(std::pair<double, double> size);

  private:
    std::string _text;
    std::pair<double, double> _size;
    enum Shape { Circle, Rectangle };
};
