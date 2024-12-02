/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PhysicsSystem.hpp
*/

#pragma once

#include "ASystem.hpp"

class PhysicsSystem : public ASystem {
  public:
    PhysicsSystem(std::vector<std::shared_ptr<Entity>>& entities);
    ~PhysicsSystem();
    void update();
    void handleMovement();
    void handleGravity();
    void handleCheckbounds();

  private:
};