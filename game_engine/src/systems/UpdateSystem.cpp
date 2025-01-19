/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Implements the `updateSystem` function, which handles the updating of
** various components within the game engine.
** Responsibility:
** - Check if entities have updatable components
** - Update the state of components based on game logic
** - Ensure synchronization between different systems
*/

#include <components/Position.hpp>
#include <components/Shape.hpp>
#include <components/Sprite.hpp>
#include <components/Text.hpp>
#include <iostream>
#include "System.hpp"

/**
 * @brief Updates the position of an entity within the game engine.
 *
 * This function updates the position of an entity identified by its ID.
 * It first checks if another entity is linked with the entity and then updates the position
 * of the entity's components (Sprite, Text, Shape) if they exist.
 *
 * @param id The ID of the entity to update.
 * @param entities A map of all entities in the game engine, indexed by their IDs.
 * @param pos A pair representing the new position (x, y) to set for the entity.
 * @param posId An identifier for the position update, used internally by the system.
 */
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

/**
 * @brief Updates the text of an entity within the game engine.
 *
 * This function updates the text of an entity identified by its ID.
 * It first checks if the entity has a Text component and then updates the text
 * of the entity.
 *
 * @param entity The entity to update.
 * @param text The new text to set for the entity.
 */
void GameEngine::System::updateText(Entity& entity, const std::string& text) {
    if (entity.hasComponent<Text>()) {
        auto& textComp = entity.getComponent<Text>();
        textComp.setString(text);
        textComp.getText().setString(text);
        textComp.getFont().loadFromFile(textComp.getFontFile());
    }
}

void GameEngine::System::updateTextFont(Entity& entity, const std::string& font) {
    if (entity.hasComponent<Text>()) {
        auto& textComp = entity.getComponent<Text>();
        textComp.getFont().loadFromFile(font);
        textComp.setFontFile(font);
    }
}

/**
 * @brief Updates the text size of an entity within the game engine.
 *
 * This function updates the text size of an entity identified by its ID.
 * It first checks if the entity has a Text component and then updates the text
 * size of the entity.
 *
 * @param id The ID of the entity to update.
 * @param entities A map of all entities in the game engine, indexed by their IDs.
 * @param textSize The new text size to set for the entity.
 */
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

/**
 * @brief Updates the texture of an entity within the game engine.
 *
 * This function updates the texture of an entity identified by its ID.
 * It first checks if the entity has a Texture component and then updates the texture
 * of the entity.
 *
 * @param entity The entity to update.
 * @param texture The new texture to set for the entity.
 */
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

/**
 * @brief Global update of an entity's component.
 *
 * This function updates any component of the entity.
 * It first checks if the entity has components and then updates
 * them.
 *
 * @param entity The entity to update.
 * @param drawable The component to update.
 * @param value The new value to set for the component.
 * @param posId An identifier for the position update, used internally by the system.
 */
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
    case UpdateType::TextFont: {
        auto textFont = std::any_cast<std::string>(value);
        updateTextFont(entity, textFont);
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