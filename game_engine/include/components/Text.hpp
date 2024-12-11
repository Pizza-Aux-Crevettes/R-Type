/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Text.hpp
*/

#pragma once

#include "Components.hpp"
#include <string>

class Text : public Component {
  public:
    Text(std::string text = "", std::string filename = "",
         unsigned int characterSize = 30);
    ~Text();
    std::string getString() const;
    sf::Font& getFont();
    unsigned int getCharacterSize() const;
    bool getIsLoaded() const;
    std::string getFontFile() const;
    sf::Text& getText();
    void setIsLoaded(bool isLoaded);
    void setString(std::string text);
    void display() const override;

  private:
    std::string _initText;
    std::string _fontFile;
    unsigned int _charSize;
    sf::Text _text;
    sf::Font _font;
    bool _isLoad = false;
};
