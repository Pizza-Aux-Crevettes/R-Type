/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** System.cpp
*/

#include "System.hpp"
#include <components/Color.hpp>
#include <components/Position.hpp>
#include <components/Sprite.hpp>
#include <components/Text.hpp>
#include <components/Texture.hpp>
#include <iostream>

GameEngine::System::System() {}

static void spriteSystem(sf::RenderWindow& window, GameEngine::Entity& entity) {
    if (entity.hasComponent<Sprite>() && entity.hasComponent<Texture>() &&
        entity.hasComponent<Position>()) {
        auto& spriteComp = entity.getComponent<Sprite>();
        auto& textureComp = entity.getComponent<Texture>();
        auto& positionComp = entity.getComponent<Position>();

        if (!textureComp.getIsLoaded()) {
            textureComp.getTexture().loadFromFile(textureComp.getTexturePath());
            textureComp.setIsLoaded(true);
        }
        if (!spriteComp.getIsLoaded()) {
            if (textureComp.getTextureRect().size() == 4) {
                const auto textureRect = textureComp.getTextureRect();
                spriteComp.getSprite().setTextureRect(
                    sf::IntRect(textureRect[0], textureRect[1], textureRect[2],
                                textureRect[3]));
            }
            spriteComp.getSprite().setTexture(textureComp.getTexture());
            spriteComp.getSprite().setPosition(positionComp.getPositionX(),
                                               positionComp.getPositionY());
            if (spriteComp.getSize().first != -1 &&
                spriteComp.getSize().second != -1) {
                spriteComp.getSprite().setScale(spriteComp.getSize().first,
                                                spriteComp.getSize().second);
            }
            if (entity.hasComponent<Color>() &&
                entity.getComponent<Color>().getColor().size() == 4) {
                auto& colorComp = entity.getComponent<Color>();
                const auto color = colorComp.getColor();
                spriteComp.getSprite().setColor(
                    sf::Color(color[0], color[1], color[2], color[3]));
            }
            spriteComp.setIsLoaded(true);
        }
        window.draw(spriteComp.getSprite());
    }
}

static void textSystem(sf::RenderWindow& window, GameEngine::Entity& entity) {
    if (entity.hasComponent<Text>() && entity.hasComponent<Position>()) {
        auto& textComp = entity.getComponent<Text>();
        auto& positionComp = entity.getComponent<Position>();

        if (!textComp.getIsLoaded()) {
            textComp.getFont().loadFromFile(textComp.getFontFile());
            textComp.getText().setFont(textComp.getFont());
            textComp.getText().setString(textComp.getString());
            textComp.getText().setCharacterSize(textComp.getCharacterSize());
            textComp.getText().setPosition(positionComp.getPositionX(),
                                           positionComp.getPositionY());
            if (entity.hasComponent<Color>() &&
                entity.getComponent<Color>().getColor().size() == 4) {
                auto& colorComp = entity.getComponent<Color>();
                const auto color = colorComp.getColor();
                textComp.getText().setColor(
                    sf::Color(color[0], color[1], color[2], color[3]));
            }
            textComp.setIsLoaded(true);
        }
        window.draw(textComp.getText());
    }
}

void GameEngine::System::render(
    sf::RenderWindow& window,
    std::map<int, std::shared_ptr<Entity>>& entities) {
    for (auto& [id, entity] : entities) {
        spriteSystem(window, *entity);
        textSystem(window, *entity);
    }
}

void GameEngine::System::update(Entity& entity, const UpdateType type,
                                std::any value) {
    switch (type) {
    case UpdateType::Position: {
        auto pos = std::any_cast<std::pair<float, float>>(value);
        entity.getComponent<Position>().setPositionX(pos.first);
        entity.getComponent<Position>().setPositionY(pos.second);
        entity.getComponent<Sprite>().getSprite().setPosition(pos.first,
                                                              pos.second);
        break;
    }
    default:;
    }
}

GameEngine::System::~System() {}