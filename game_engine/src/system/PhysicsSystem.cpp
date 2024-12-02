/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Implements the `PhysicsSystem`, which simulates physical
** interactions and updates entity positions and velocities.
** Responsibilities:
** - Apply physics laws such as gravity and bounce.
** - Update entity positions and velocities over time.
** - Integrate with the collision system to handle physical responses.

*/

#include "system/PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem(std::vector<std::shared_ptr<Entity>>& entities)
    : ASystem(entities) {}

PhysicsSystem::~PhysicsSystem() {}

void PhysicsSystem::update() {}
