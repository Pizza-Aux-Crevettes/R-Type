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

    static LifeBar& get();
    GameEngine::Entity
    createEntityText(int, std::string text, const std::vector<std::pair<float, float>>, unsigned int);

    void displayLifeBar(sf::RenderWindow&, GameEngine::System);

    int getHp() const;
    void setHp(int newHp);

    int getPlayerId();
    void setPlayerId(int playerId);

    void manageHealth(int entityId, int health);

    protected:
    private:
        int _playerId;
        std::map<int, GameEngine::Entity> _entitiesLifeBar;
        int _hp = 100;
        bool _entitiesInitialized = false;
};

