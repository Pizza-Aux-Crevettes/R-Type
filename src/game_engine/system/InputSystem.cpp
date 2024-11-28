/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Implements the `InputSystem`, responsible for handling player
** input from various sources (e.g., keyboard, mouse, or gamepad).
** Responsibilities:
** - Poll input devices and process input events.
** - Translate raw input into actions or commands for the game.
** - Communicate player actions to other systems or entities.
*/

#include "../../../include/game_engine/system/InputSystem.hpp"

InputSystem::InputSystem(std::vector<std::shared_ptr<Entity>>& entities) : ASystem(entities)
{

}

InputSystem::~InputSystem()
{

}