/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sprite.hpp
*/

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <string>
#include <vector>

class Sprite {
    public:
        Sprite(std::string texturePath = "", std::vector<double> size = {0.0, 0.0});
        ~Sprite();
        std::string getTexturePath() const;
        void setTexturePath(std::string texturePath);
        std::vector<double> getSize() const;
        void setSize(std::vector<double> size);

    private:
        std::string _texturePath;
        std::vector<double> _size;
};

#endif /* SPRITE_HPP_ */
