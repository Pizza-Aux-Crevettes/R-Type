/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** RenderSystem.hpp
*/

#pragma once

#include "ASystem.hpp"

class RenderSystem : public ASystem
{
  private:
  public:
    RenderSystem(std::vector<std::shared_ptr<Entity>> &entities);
    ~RenderSystem();
    void update();
    void displaySprite();
    void displayText();
    void handleAnimations();
    void handleSound();
    void displayButton();
};