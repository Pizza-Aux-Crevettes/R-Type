/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** System.cpp
*/

#include <components/Position.hpp>
#include <components/Sprite.hpp>
#include <components/Text.hpp>
#include "System.hpp"

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
        linkSystem(id, entities, pos, posId);
        if (entity.hasComponent<Sprite>()) {
            updatePos(entity, entity.getComponent<Sprite>().getSprite(), pos,
                      posId);
        }
        if (entity.hasComponent<Text>()) {
            updatePos(entity, entity.getComponent<Text>().getText(), pos,
                      posId);
        }
        break;
    }
    default:;
    }
}