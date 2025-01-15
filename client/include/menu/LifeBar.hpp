/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** LifeBar
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <System.hpp>
#include <iostream>

class LifeBar {
    public:
        LifeBar();
        ~LifeBar();

    GameEngine::Entity
    createEntityText(int, const std::string,
                     const std::vector<std::pair<float, float>>, unsigned int);

    void displayLifeBar(sf::RenderWindow&, GameEngine::System);

    int getHp() const;
    void setHp(int newHp);

    protected:
    private:
        std::map<int, GameEngine::Entity> _entitiesLifeBar;
        int _hp = 100;
        bool _entitiesInitialized = false;
};

