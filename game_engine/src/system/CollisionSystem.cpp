/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Implements the `CollisionSystem`, which handles collision
** detection between entities in the game world.
** Responsibilities:
** - Detect and resolve collisions between entities.
** - Determine when entities should interact (e.g., take damage).
** - Update the game state based on collision events.

*/

#include "system/CollisionSystem.hpp"

CollisionSystem::CollisionSystem(std::vector<std::shared_ptr<Entity>>& entities)
    : ASystem(entities) {}

CollisionSystem::~CollisionSystem() {}

void CollisionSystem::update() {}
