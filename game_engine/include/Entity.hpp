/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Entity.hpp
*/

#pragma once

#include <cstdint>
#include <vector>

class Entity {
  private:
    std::int32_t _id;
    // std::vector<T component>;
  public:
    Entity();
    ~Entity();
    std::int32_t getEntityId();
};