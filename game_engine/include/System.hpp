/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** System.hpp
*/

#pragma once
#include "Entity.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <any>
#include <memory>

namespace GameEngine {

enum class UpdateType { Position, Health, Velocity };

class System {
  public:
    System();
    ~System();
    void onClick(sf::RenderWindow& window, std::map<int, Entity>& entities,
                 sf::Vector2i mousePos);
    void render(sf::RenderWindow& window, std::map<int, Entity>& entities);
    void update(Entity& entity, UpdateType type, std::any value);
};

} // namespace GameEngine
