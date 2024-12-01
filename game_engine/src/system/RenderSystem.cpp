/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Implements the `RenderSystem`, which handles drawing entities
** and other visual elements to the screen.
** Responsibilities:
** - Maintain a rendering pipeline for drawing entities and effects.
** - Sort and render entities based on their visual properties (e.g., depth).
** - Manage integration with SMFL
*/

#include "system/RenderSystem.hpp"

RenderSystem::RenderSystem(std::vector<std::shared_ptr<Entity>> &entities) : ASystem(entities) {}

RenderSystem::~RenderSystem() {}

void RenderSystem::update() {}
