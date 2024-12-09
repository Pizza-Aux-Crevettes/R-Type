/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Text.hpp
*/

#pragma once

#include <string>
#include "Components.hpp"

class Text : public Component {
  public:
    Text(std::string text = "");
    ~Text();
    std::string getText() const;
    void setText(std::string text);
    void display() const override;

  private:
    std::string _text;
};
