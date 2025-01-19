/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** BossLifeBar
*/

#include "health/BossLifeBar.hpp"
#include "components/Color.hpp"
#include "components/Position.hpp"
#include "components/Text.hpp"
#include "menu/OptionMenu.hpp"

BossLifeBar::BossLifeBar(){}

BossLifeBar::~BossLifeBar(){}


BossLifeBar& BossLifeBar::get() {
    static BossLifeBar instance;
    return instance;
}

GameEngine::Entity BossLifeBar::createEntityText(
    int id, std::string text,
    const std::vector<std::pair<float, float>> position,
    unsigned int fontSize) {

    auto newEntity = GameEngine::Entity(id);
    int hp = BossLifeBar::get().getHp();
    std::vector<double> color;

    if (text != "BOSS HEALTH") {
        if (hp > 700) {
            color = {0, 255, 0, 255};  // Vert
        } else if (hp > 500) {
            color = {255, 255, 0, 255};  // Jaune
        } else if (hp > 300) {
            color = {255, 165, 0, 255};  // Orange
        } else {
            color = {255, 0, 0, 255};  // Rouge
        }
    }

    newEntity.addComponent(Text(text, OptionMenu::get().getAdaptabilityText(), fontSize));
    newEntity.addComponent(Position(position));
    newEntity.addComponent(Color(color));
    return newEntity;
}

void BossLifeBar::displayBossLifeBar(sf::RenderWindow& window,
                                   GameEngine::System system) {
    static int previousHp = -1;
    int hp = BossLifeBar::get().getHp();

    if (!_entitiesInitialized) {
        _entitiesBossLifeBar.emplace(0, createEntityText(0, std::to_string(hp), {{965, 20}}, 30));
        _entitiesBossLifeBar.emplace(1, createEntityText(1, "BOSS HEALTH", {{1050, 20}}, 30));
        _entitiesInitialized = true;
        previousHp = hp;
    }
    _entitiesBossLifeBar.erase(0);
    _entitiesBossLifeBar.emplace(0, createEntityText(0, std::to_string(hp), {{965, 20}}, 30));
    system.render(window, _entitiesBossLifeBar);                        
}

int BossLifeBar::getHp() const {
    return this->_hp;
}

void BossLifeBar::setHp(int newHp) {
    if (newHp <= 0) {
        this->_hp = 0;
    } else {
        this->_hp = newHp;
    }
}

int BossLifeBar::getBossId() {
    return _bossId;
}

void BossLifeBar::setBossId(int bossId) {
    _bossId = bossId;
}


void BossLifeBar::manageHealth(int entityId, int health) {
    if (BossLifeBar::get().getBossId() == entityId) {
        BossLifeBar::get().setHp(health);
    }
}