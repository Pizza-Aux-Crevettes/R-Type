/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Renderable.hpp
*/

#ifndef RENDERABLE_HPP_
#define RENDERABLE_HPP_

class Renderable {
    public:
        Renderable(bool isVisible = true);
        ~Renderable();
        bool getIsVisible() const;
        void setIsVisible(bool isVisible);

    private:
        bool _isVisible;
};

#endif /* RENDERABLE_HPP_ */
