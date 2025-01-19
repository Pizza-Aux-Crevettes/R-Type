/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** This file implements the WinMenu class, which is responsible for creating and
** managing the win menu interface. The class provides functionalities to create
** and display various elements, such as buttons, text, sprites, and other
** components on the win menu screen. It also includes methods to handle user
** interaction, such as clicking the Quit Game button to exit the game.
** WinMenu.cpp
*/

#include "menu/WinMenu.hpp"
#include "menu/OptionMenu.hpp"
#include <components/Button.hpp>
#include <components/ButtonRect.hpp>
#include <components/Text.hpp>
#include <components/Texture.hpp>
#include <components/Sprite.hpp>
#include <util/getResponsiveValue.hpp>


WinMenu::WinMenu(){}

WinMenu::~WinMenu(){}

WinMenu& WinMenu::get() {
    static WinMenu instance;
    return instance;
}

GameEngine::Entity WinMenu::createEntityButton(int id, std::string title, std::string font, int fontSize, std::vector<std::pair<float, float>> position, std::function<void()> callback) {
    auto newEntity = GameEngine::Entity(id);
    auto button = Button(title, font, fontSize);
    button.setCallback(callback);
    newEntity.addComponent(button);
    newEntity.addComponent(Position(position));
    newEntity.addComponent(Color({255, 255, 255, 255}));
    return newEntity;
}


GameEngine::Entity WinMenu::createEntityText(int id, const std::string text, const std::vector<std::pair<float, float>> position, unsigned int fontSize) {
    auto newEntity = GameEngine::Entity(id);
    newEntity.addComponent(Text(text, OptionMenu::get().getAdaptabilityText(), fontSize));
    newEntity.addComponent(Position(position));
    if (text != "QUIT GAME")
        newEntity.addComponent(Color({34, 139, 34, 255}));
    else
        newEntity.addComponent(Color({255, 255, 255, 255}));
    return newEntity;
}

GameEngine::Entity WinMenu::createEntitySprite(int id, const std::pair<float, float> size, std::string texture, std::vector<int> textureRect, const std::vector<std::pair<float, float>> position) {
    auto newEntity = GameEngine::Entity(id);
    newEntity.addComponent(Sprite(size));
    newEntity.addComponent(Texture(texture, textureRect));
    newEntity.addComponent(Position(position));
    return newEntity;
}

GameEngine::Entity WinMenu::createEntityRect(
    int id, const std::pair<int, int> size,
    const std::vector<std::pair<float, float>> position, sf::Color color,
    std::function<void()> callback) {
    auto rectEntity = GameEngine::Entity(id);
    auto buttonRect = ButtonRect(size, color, true);
    buttonRect.setCallback(callback);
    rectEntity.addComponent(buttonRect);
    rectEntity.addComponent(Position(position));
    return rectEntity;
}

void WinMenu::isClickedExit(sf::RenderWindow& window) {
    window.close();
}

void WinMenu::displayWnMenu(sf::RenderWindow& window, GameEngine::System system) {
    GetResponsiveValue responsive;
    int currentWidth = window.getSize().x;
    int currentHeight = window.getSize().y;

    if (!_entitiesInitialized) {
        int entityId = 0;

        _entitiesWinMenu.emplace(entityId, createEntitySprite(entityId++, {responsive.getResponsiveSizeX(1920, currentWidth, 5), responsive.getResponsiveSizeY(1080, currentHeight, 5)},
                    "assets/sprite/space.png", {0, 0, 400, 400},
                    {{responsive.getResponsivePosX(1920, currentWidth, -400),
                      responsive.getResponsivePosY(1080, currentHeight,
                                                   -170)}}));
        _entitiesWinMenu.emplace(
            entityId,
            createEntitySprite(
                entityId++,
                {responsive.getResponsiveSizeX(1920, currentWidth, 6),
                responsive.getResponsiveSizeY(1080, currentHeight, 6)},
                "assets/sprite/spaceship.png", {0, 18, 34, 15},
                {{responsive.getResponsivePosX(1920, currentWidth, 30),
                  responsive.getResponsivePosY(1080, currentHeight,
                                             100)}}));
        _entitiesWinMenu.emplace(
            entityId,
            createEntitySprite(
                entityId++,
                {responsive.getResponsiveSizeX(1920, currentWidth, 5),
                    responsive.getResponsiveSizeY(1080, currentHeight, 5)},
                "assets/sprite/shoot_blue.png", {165, 0, 65, 15},
                {{responsive.getResponsivePosX(1920, currentWidth, 350),
                    responsive.getResponsivePosY(1080, currentHeight,
                                                100)}}));
        _entitiesWinMenu.emplace(
            entityId,
            createEntitySprite(
                entityId++,
                {responsive.getResponsiveSizeX(1920, currentWidth, 5),
                    responsive.getResponsiveSizeY(1080, currentHeight, 5)},
                "assets/sprite/enemy.png", {0, 0, 50, 80},
                {{responsive.getResponsivePosX(1920, currentWidth, 180),
                    responsive.getResponsivePosY(1080, currentHeight,
                                                820)}}));
        _entitiesWinMenu.emplace(
            entityId,
            createEntitySprite(
                entityId++,
                {responsive.getResponsiveSizeX(1920, currentWidth, 5),
                    responsive.getResponsiveSizeY(1080, currentHeight, 5)},
                "assets/sprite/canon.png", {165, 0, 33, 30},
                {{responsive.getResponsivePosX(1920, currentWidth, 1600),
                    responsive.getResponsivePosY(1080, currentHeight,
                                                -50)}}));
        _entitiesWinMenu.emplace(
            entityId,
            createEntitySprite(
                entityId++,
                {responsive.getResponsiveSizeX(1920, currentWidth, 5),
                    responsive.getResponsiveSizeY(1080, currentHeight, 5)},
                "assets/sprite/canon.png", {33, 33, 33, 30},
                {{responsive.getResponsivePosX(1920, currentWidth, 1600),
                    responsive.getResponsivePosY(1080, currentHeight,
                                                970)}}));

        _entitiesWinMenu.emplace(
            entityId,
            createEntitySprite(
                entityId++,
                {responsive.getResponsiveSizeX(1920, currentWidth, 5),
                    responsive.getResponsiveSizeY(1080, currentHeight, 5)},
                "assets/sprite/intact-boss.png", {0, 0, 200, 200},
                {{responsive.getResponsivePosX(1920, currentWidth, 1400),
                    responsive.getResponsivePosY(1080, currentHeight,
                                                -65)}}));
        _entitiesWinMenu.emplace(entityId, createEntityText(entityId++, "YOU WIN", {{550, 300}}, 40));
        _entitiesWinMenu.emplace(
            entityId, createEntityText(entityId++, "QUIT GAME", {{
                responsive.getResponsivePosX(1920, currentWidth, 860),
                responsive.getResponsivePosY(1080, currentHeight, 630)}}, 25));
        _entitiesWinMenu.emplace(
            entityId,
            createEntityRect(
                entityId++, {165, 50},
                {{responsive.getResponsivePosX(1920, currentWidth, 845), responsive.getResponsivePosY(1080, currentHeight, 615)}},
                sf::Color::White, [this, &window]() { isClickedExit(window); }));
        _entitiesInitialized = true;
    }
    system.render(window, _entitiesWinMenu);
}
