/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UpdateSystem.cpp
*/

#include <components/Position.hpp>
#include <components/Shape.hpp>
#include <components/Sprite.hpp>
#include <components/Text.hpp>
#include "System.hpp"

void GameEngine::System::updateEntityPosition(
    const int id, std::map<int, Entity>& entities,
    const std::pair<float, float>& pos, const int posId) {
    linkSystem(id, entities, pos, posId);
    Entity& entity = entities.at(id);
    if (entity.hasComponent<Sprite>()) {
        updatePos(entity, entity.getComponent<Sprite>().getSprite(), pos,
                  posId);
    }
    if (entity.hasComponent<Text>()) {
        updatePos(entity, entity.getComponent<Text>().getText(), pos, posId);
    }
    if (entity.hasComponent<Shape>()) {
        if (entity.getComponent<Shape>().getShapeType() == Rectangle) {
            updatePos(entity, entity.getComponent<Shape>().getRect(), pos,
                      posId);
        } else {
            updatePos(entity, entity.getComponent<Shape>().getCircle(), pos,
                      posId);
        }
    }
}

void GameEngine::System::updateText(Entity& entity, const std::string& text) {
    if (entity.hasComponent<Text>()) {
        auto& textComp = entity.getComponent<Text>();
        textComp.setString(text);
        textComp.getText().setString(text);
    }
}

void GameEngine::System::updateTextSize(const int id,
                                        std::map<int, Entity>& entities,
                                        const unsigned int textSize) {
    Entity& entity = entities.at(id);
    if (entity.hasComponent<Text>()) {
        auto& textComp = entity.getComponent<Text>();
        textComp.setCharacterSize(textSize);
        textComp.getText().setCharacterSize(textSize);
    }
}

void GameEngine::System::updateTexture(Entity& entity, std::string& texture) {
    if (entity.hasComponent<Texture>()) {
        auto& textureComp = entity.getComponent<Texture>();
        textureComp.setTexturePath(texture);
        textureComp.getTexture().loadFromFile(textureComp.getTexturePath());
        if (entity.hasComponent<Sprite>()) {
            auto& spriteComp = entity.getComponent<Sprite>();
            spriteComp.getSprite().setTexture(textureComp.getTexture());
        }
        if (entity.hasComponent<Shape>()) {
            auto& shapeComp = entity.getComponent<Shape>();
            if (shapeComp.getShapeType() == Circle) {
                shapeComp.getCircle().setTexture(&textureComp.getTexture());
            }
            if (shapeComp.getShapeType() == Rectangle) {
                shapeComp.getRect().setTexture(&textureComp.getTexture());
            }
        }
    }
}

void GameEngine::System::update(const int id, std::map<int, Entity>& entities,
                                const UpdateType type, const std::any& value,
                                const int posId) {
    if (!entities.contains(id)) {
        return;
    }
    Entity& entity = entities.at(id);
    switch (type) {
    case UpdateType::Position: {
        auto pos = std::any_cast<std::pair<float, float>>(value);
        updateEntityPosition(id, entities, pos, posId);
        break;
    }
    case UpdateType::Text: {
        auto text = std::any_cast<std::string>(value);
        updateText(entity, text);
        break;
    }
    case UpdateType::TextSize: {
        auto textSize = std::any_cast<unsigned int>(value);
        updateTextSize(id, entities, textSize);
        break;
    }
    case UpdateType::Texture: {
        auto texture = std::any_cast<std::string>(value);
        updateTexture(entity, texture);
        break;
    }
    default:
        break;
    }
}