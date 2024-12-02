/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position.hpp
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

class Position {
    public:
        Position(float x = 0.0f, float y = 0.0f);
        ~Position();
        float getPositionX() const;
        void setPositionX(float x);
        float getPositionY() const;
        void setPositionY(float y);

    private:
        float _x;
        float _y;
};

#endif /* POSITION_HPP_ */
