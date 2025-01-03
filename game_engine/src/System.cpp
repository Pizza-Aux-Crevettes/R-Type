/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** System.cpp
*/

#include "System.hpp"
#include <components/Color.hpp>
#include <components/Link.hpp>
#include <components/Position.hpp>
#include <components/Sprite.hpp>
#include <components/Text.hpp>
#include <components/Texture.hpp>
#include <iostream>

GameEngine::System::System() {}

template <typename Drawable>
static void updatePos(GameEngine::Entity& entity, Drawable& drawable,
                      const std::pair<float, float>& pos) {
    if (entity.hasComponent<Position>()) {
        auto& positionComp = entity.getComponent<Position>();
        positionComp.setPositionX(pos.first);
        positionComp.setPositionY(pos.second);
        drawable.setPosition(pos.first, pos.second);
    }
}

template <typename Drawable>
void setColor(GameEngine::Entity& entity, Drawable& drawable) {
    if (entity.hasComponent<Color>() &&
        entity.getComponent<Color>().getColor().size() == 4) {
        auto& colorComp = entity.getComponent<Color>();
        const auto& color = colorComp.getColor();
        if constexpr (std::is_same_v<Drawable, sf::Sprite>) {
            drawable.setColor(
                sf::Color(color[0], color[1], color[2], color[3]));
        } else if constexpr (std::is_same_v<Drawable, sf::Text>) {
            drawable.setFillColor(
                sf::Color(color[0], color[1], color[2], color[3]));
        }
    }
}

template <typename Drawable>
static void setPosition(GameEngine::Entity& entity, Drawable& drawable) {
    if (entity.hasComponent<Position>()) {
        auto& positionComp = entity.getComponent<Position>();
        drawable.setPosition(positionComp.getPositionX(),
                             positionComp.getPositionY());
    }
}

static void linkSystem(int id, std::map<int, GameEngine::Entity>& entities,
                       std::pair<float, float> newLinkedEntityPos) {
    for (int i = 0; i < entities.size(); i++) {
        if (entities[i].hasComponent<Link>() &&
            entities[i].getComponent<Link>().getId() == id) {
            GameEngine::Entity entity = entities[i];
            GameEngine::Entity entityLinked = entities[id];
            auto oldLinkedEntityPos = entityLinked.getComponent<Position>();
            const std::pair dist = {
                newLinkedEntityPos.first - oldLinkedEntityPos.getPositionX(),
                newLinkedEntityPos.second - oldLinkedEntityPos.getPositionY()};
            auto entityPos = entity.getComponent<Position>();
            const std::pair newPos = {entityPos.getPositionX() + dist.first,
                                      entityPos.getPositionY() + dist.second};
            if (entity.hasComponent<Sprite>()) {
                updatePos(entity, entity.getComponent<Sprite>().getSprite(),
                          newPos);
            }
            if (entity.hasComponent<Text>()) {
                updatePos(entity, entity.getComponent<Text>().getText(),
                          newPos);
            }
        }
    }
}

static void spriteSystem(sf::RenderWindow& window, GameEngine::Entity& entity) {
    if (entity.hasComponent<Sprite>() && entity.hasComponent<Texture>() &&
        entity.hasComponent<Position>()) {
        auto& spriteComp = entity.getComponent<Sprite>();
        auto& textureComp = entity.getComponent<Texture>();
        if (!textureComp.getIsLoaded()) {
            textureComp.getTexture().loadFromFile(textureComp.getTexturePath());
            textureComp.setIsLoaded(true);
        }
        if (!spriteComp.getIsLoaded()) {
            if (textureComp.getTextureRect().size() == 4) {
                const auto& textureRect = textureComp.getTextureRect();
                spriteComp.getSprite().setTextureRect(
                    sf::IntRect(textureRect[0], textureRect[1], textureRect[2],
                                textureRect[3]));
            }
            spriteComp.getSprite().setTexture(textureComp.getTexture());
            setPosition(entity, spriteComp.getSprite());
            if (spriteComp.getSize().first != -1 &&
                spriteComp.getSize().second != -1) {
                spriteComp.getSprite().setScale(spriteComp.getSize().first,
                                                spriteComp.getSize().second);
            }
            setColor(entity, spriteComp.getSprite());
            spriteComp.setIsLoaded(true);
        }
        window.draw(spriteComp.getSprite());
    }
}

static void textSystem(sf::RenderWindow& window, GameEngine::Entity& entity) {
    if (entity.hasComponent<Text>() && entity.hasComponent<Position>()) {
        auto& textComp = entity.getComponent<Text>();
        if (!textComp.getIsLoaded()) {
            textComp.getFont().loadFromFile(textComp.getFontFile());
            textComp.getText().setFont(textComp.getFont());
            textComp.getText().setString(textComp.getString());
            textComp.getText().setCharacterSize(textComp.getCharacterSize());
            setPosition(entity, textComp.getText());
            setColor(entity, textComp.getText());
            textComp.setIsLoaded(true);
        }
        window.draw(textComp.getText());
    }
}

void GameEngine::System::render(sf::RenderWindow& window,
                                std::map<int, Entity>& entities) {
    for (auto& [id, entity] : entities) {
        spriteSystem(window, entity);
        textSystem(window, entity);
    }
}

void GameEngine::System::update(int id, std::map<int, Entity>& entities,
                                const UpdateType type, std::any value) {
    Entity entity = entities[id];
    switch (type) {
    case UpdateType::Position: {
        auto pos = std::any_cast<std::pair<float, float>>(value);
        linkSystem(id, entities, pos);
        if (entity.hasComponent<Sprite>()) {
            updatePos(entity, entity.getComponent<Sprite>().getSprite(), pos);
        }
        if (entity.hasComponent<Text>()) {
            updatePos(entity, entity.getComponent<Text>().getText(), pos);
        }
        break;
    }
    default:;
    }
}

GameEngine::System::~System() {}