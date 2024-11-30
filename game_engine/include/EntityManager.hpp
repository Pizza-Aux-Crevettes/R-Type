/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** EntityManager.hpp
*/

#pragma once

#include "Entity.hpp"
#include <vector>
#include <memory>

class EntityManager
{
    private:
        std::vector<std::shared_ptr<Entity>>entities;
    public:
        EntityManager();
        ~EntityManager();
        void createEntity();
        void destroyEntity();
        // void addComponent(Entity entity, T component);
        // void destroyComponent(Entity entity, T component);
        void getComponent(Entity entity);
        void getEntities();
};