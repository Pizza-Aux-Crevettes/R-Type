/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Implements the `Entity` class, which represents a game object.
** Each `Entity` can have various components attached to it, enabling it to
** have specific behaviors or properties.
** Responsibility:
** - Store an entity's unique ID
*/

#include "Entity.hpp"
#include <iostream>

GameEngine::Entity::Entity() : _id(0) {}

GameEngine::Entity::~Entity() {}

std::int32_t GameEngine::Entity::getEntityId() const {
    return (_id);
}

void GameEngine::Entity::displayComponents() const {
    for (auto& component : _components) {
        component.second->display();
    }
}
