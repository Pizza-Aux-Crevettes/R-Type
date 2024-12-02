/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** CollisionSystem.hpp
*/

#pragma once

#include "ASystem.hpp"

class CollisionSystem : public ASystem
{
    public:
        CollisionSystem(std::vector<std::shared_ptr<Entity>>& entities);
        ~CollisionSystem();
        void update();
        void isColliding();
        void damage();
    private:
};