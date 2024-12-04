/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Text.hpp
*/

#pragma once

#include <string>

class Text {
  public:
    Text(std::string text = "");
    ~Text();
    std::string getText() const;
    void setText(std::string text);

  private:
    std::string _text;
};
