/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** System.cpp
*/

#include "System.hpp"
#include <components/Link.hpp>
#include <components/Sprite.hpp>
#include <components/Text.hpp>

void GameEngine::System::linkSystem(int id, std::map<int, GameEngine::Entity>& entities,
                       std::pair<float, float> newLinkedEntityPos,
                       const int posId) {
    for (auto& [_, entity] : entities) {
        if (entity.hasComponent<Link>() &&
            entity.getComponent<Link>().getId() == id) {
            GameEngine::Entity entityLinked = entities[id];
            auto oldLinkedEntityPos = entityLinked.getComponent<Position>();
            const std::pair dist = {newLinkedEntityPos.first -
                                        oldLinkedEntityPos.getPositionX(posId),
                                    newLinkedEntityPos.second -
                                        oldLinkedEntityPos.getPositionY(posId)};
            auto entityPos = entity.getComponent<Position>();
            const std::pair newPos = {entityPos.getPositionX(0) + dist.first,
                                      entityPos.getPositionY(0) + dist.second};
            if (entity.hasComponent<Sprite>()) {
                updatePos(entity, entity.getComponent<Sprite>().getSprite(),
                          newPos, 0);
            }
            if (entity.hasComponent<Text>()) {
                updatePos(entity, entity.getComponent<Text>().getText(), newPos,
                          0);
            }
        }
    }
}
