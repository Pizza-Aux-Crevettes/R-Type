/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** BossLifeBar
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <System.hpp>
#include <iostream>

class BossLifeBar {
    public:
        BossLifeBar();
        ~BossLifeBar();

        static BossLifeBar& get();
        GameEngine::Entity
        createEntityText(int, std::string text, const std::vector<std::pair<float, float>>, unsigned int);

        void displayBossLifeBar(sf::RenderWindow&, GameEngine::System);

        int getHp() const;
        void setHp(int newHp);

        int getBossId();
        void setBossId(int bossId);

        void manageHealth(int entityId, int health);

    protected:
    private:
        int _bossId;
        std::map<int, GameEngine::Entity> _entitiesBossLifeBar;
        int _hp = 1000;
        bool _entitiesInitialized = false;
};

