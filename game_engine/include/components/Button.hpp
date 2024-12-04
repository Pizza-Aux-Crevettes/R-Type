/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Button.hpp
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "Components.hpp"
#include <SFML/Graphics.hpp>
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

  private:
    std::string _text;
    std::pair<double, double> _size;
    enum Shape { Circle, Rectangle };
};

#endif /* BUTTON_HPP_ */
