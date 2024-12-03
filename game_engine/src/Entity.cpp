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

Entity::Entity() {}

Entity::~Entity() {}

std::int32_t Entity::getEntityId() {
    return (_id);
}