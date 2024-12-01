/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** ISystem.hpp
*/

#pragma once

#include "../Entity.hpp"

class ISystem
{
  public:
    virtual ~ISystem() = default;
    virtual void update() = 0;
};
