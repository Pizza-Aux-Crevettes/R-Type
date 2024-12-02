/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Text.hpp
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

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

#endif /* TEXT_HPP_ */

