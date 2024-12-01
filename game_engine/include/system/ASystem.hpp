/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** ASystem.hpp
*/

#pragma once

#include "ISystem.hpp"
#include <memory>
#include <vector>

class ASystem : public ISystem
{
  public:
    explicit ASystem(std::vector<std::shared_ptr<Entity>> &entities) : entities(entities) {}
    virtual ~ASystem() = default;

  protected:
    std::vector<bool> _active;
    std::vector<std::shared_ptr<Entity>> &entities;
};