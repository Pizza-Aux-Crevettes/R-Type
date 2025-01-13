/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** System.cpp
*/

#include "System.hpp"

GameEngine::System::System() {}

void GameEngine::System::render(sf::RenderWindow& window,
                                std::map<int, Entity>& entities) {
    for (auto& [id, entity] : entities) {
        spriteSystem(window, entity);
        textSystem(window, entity);
        buttonSystem(window, entity);
        buttonRectSystem(window, entity);
        optionButtonSystem(window, entity);
        sliderSystem(window, entity, entities);
        shapeSystem(window, entity);
    }
}

GameEngine::System::~System() {}
