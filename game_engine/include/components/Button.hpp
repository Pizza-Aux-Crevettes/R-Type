/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Button.hpp
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <string>
#include <SFML/Graphics.hpp>

class Button {
    public:
        Button(std::string text = "", sf::Vector2f size = sf::Vector2f(0.0f, 0.0f));
        ~Button();
        std::string getText() const;
        void setText(std::string text);
        sf::Vector2f getSize() const;
        void setSize(sf::Vector2f size);

    private:
        std::string _text;
        sf::Vector2f _size;
};

#endif /* BUTTON_HPP_ */
