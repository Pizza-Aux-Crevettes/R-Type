/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Button.hpp
*/

#pragma once

#include <string>
#include <functional>
#include "Components.hpp"

class Button : public Component {
  public:
    Button(std::string text = "", std::pair<double, double> size = {0.0, 0.0});
    ~Button();
    std::string getText() const;
    void setText(std::string text);
    std::pair<double, double> getSize() const;
    void setSize(std::pair<double, double> size);
    sf::RectangleShape& getShape();
    void setShape(const sf::RectangleShape&);
    bool getIsLoaded() const;
    void setIsLoaded();
    bool getChecked() const;
    void setChecked();
    void setCallback(std::function<void()>);
    void executeCallback();
    void display() const override;

  private:
    std::string _text;
    std::pair<double, double> _size;
    enum Shape { Circle, Rectangle };
    sf::RectangleShape _button;
    bool _isLoad = false;
    bool _isChecked = false;
    std::function<void()> _callback;
};
