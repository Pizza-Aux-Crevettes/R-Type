/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** This file contains the implementation of the LifeBar class, which manages 
** the player's health display. It creates and updates the health bar, adjusts 
** the health value based on game events, and renders the health text on the screen. 
** The health bar changes color based on the remaining health, ranging from green 
** for high health to red for low health.
** LifeBar.cpp
*/

#include "health/LifeBar.hpp"
#include "components/Color.hpp"
#include "components/Position.hpp"
#include "components/Text.hpp"
#include "menu/OptionMenu.hpp"
#include "util/getResponsiveValue.hpp"

LifeBar::LifeBar(){}

LifeBar::~LifeBar(){}

LifeBar& LifeBar::get() {
    static LifeBar instance;
    return instance;
}

GameEngine::Entity LifeBar::createEntityText(
    int id, std::string text,
    const std::vector<std::pair<float, float>> position,
    unsigned int fontSize) {

    auto newEntity = GameEngine::Entity(id);
    int hp = LifeBar::get().getHp();
    std::vector<double> color;

    if (text != "HEALTH") {
        if (hp > 70) {
            color = {0, 255, 0, 255};  // Vert
        } else if (hp > 50) {
            color = {255, 255, 0, 255};  // Jaune
        } else if (hp > 30) {
            color = {255, 165, 0, 255};  // Orange
        } else {
            color = {255, 0, 0, 255};  // Rouge
        }
    }
    newEntity.addComponent(Text(text, OptionMenu::get().getAdaptabilityText(),
                         (fontSize * OptionMenu::get().getFontSize() / 100.0f)));
    newEntity.addComponent(Position(position));
    newEntity.addComponent(Color(color));
    return newEntity;
}

void LifeBar::displayLifeBar(sf::RenderWindow& window,
                             GameEngine::System system) {
    GetResponsiveValue responsive;
    int currentWidth = window.getSize().x;
    int currentHeight = window.getSize().y;
    static int previousHp = -1;
    int hp = LifeBar::get().getHp();

    if (!_entitiesInitialized) {
        _entitiesLifeBar.emplace(0, createEntityText(0, std::to_string(hp),
                    {{responsive.getResponsivePosX(800, currentWidth, 60),
                    responsive.getResponsivePosY(600, currentHeight, 50)}}, 30));
        _entitiesLifeBar.emplace(1, createEntityText(1, "HEALTH", 
                    {{responsive.getResponsivePosX(800, currentWidth, 60),
                    responsive.getResponsivePosY(600, currentHeight, 20)}}, 25));
        _entitiesInitialized = true;
        previousHp = hp;
    }
    if (hp != previousHp) {
        _entitiesLifeBar.erase(0);
        _entitiesLifeBar.emplace(0, createEntityText(0, std::to_string(hp),
                    {{responsive.getResponsivePosX(800, currentWidth, 60),
                    responsive.getResponsivePosY(600, currentHeight, 50)}}, 30));
        previousHp = hp;
    }
    system.render(window, _entitiesLifeBar);
}


int LifeBar::getHp() const {
    return this->_hp;
}

void LifeBar::setHp(int newHp) {
    if (newHp <= 0) {
        this->_hp = 0;
    } else {
        this->_hp = newHp;
    }
}

int LifeBar::getPlayerId() {
    return _playerId;
}

void LifeBar::setPlayerId(int playerId) {
    _playerId = playerId;
}


void LifeBar::manageHealth(int entityId, int health) {
    if (LifeBar::get().getPlayerId() == entityId) {
        LifeBar::get().setHp(health);
    }
}
