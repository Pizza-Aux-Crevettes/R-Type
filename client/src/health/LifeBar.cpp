/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** LifeBar
*/

#include "health/LifeBar.hpp"
#include "components/Color.hpp"
#include "components/Position.hpp"
#include "components/Text.hpp"

LifeBar::LifeBar(){}

LifeBar::~LifeBar(){}

LifeBar& LifeBar::get() {
    static LifeBar instance;
    return instance;
}

GameEngine::Entity LifeBar::createEntityText(
    int id, const std::string text,
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

    newEntity.addComponent(Text(text, "assets/font/Inter_Bold.ttf", fontSize));
    newEntity.addComponent(Position(position));
    newEntity.addComponent(Color(color));
    return newEntity;
}

void LifeBar::displayLifeBar(sf::RenderWindow& window,
                                   GameEngine::System system) {
    static int previousHp = -1;
    int hp = LifeBar::get().getHp();

    if (!_entitiesInitialized) {
        _entitiesLifeBar.emplace(0, createEntityText(0, std::to_string(hp), {{20, 20}}, 30));
        _entitiesLifeBar.emplace(1, createEntityText(1, "HEALTH", {{80, 20}}, 30));
        _entitiesInitialized = true;
        previousHp = hp;
    }
    _entitiesLifeBar.erase(0);
    _entitiesLifeBar.emplace(0, createEntityText(0, std::to_string(hp), {{20, 20}}, 30));
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
