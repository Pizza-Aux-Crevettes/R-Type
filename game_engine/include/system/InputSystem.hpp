/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** InputSystem.hpp
*/

#pragma once

#include "ASystem.hpp"

class InputSystem : public ASystem
{
    public:
        InputSystem(std::vector<std::shared_ptr<Entity>>& entities);
        ~InputSystem();
        void update();
        void handleKeyBoard();
        void handleMouse();
    private:
};