/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** System.hpp
*/

#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <any>
#include <memory>
#include "Entity.hpp"

namespace GameEngine {

enum class UpdateType { Position, Health, Velocity };

class System {
  public:
    System();
    ~System();
    void onClick(sf::RenderWindow& window, std::map<int, Entity>& entities,
                 sf::Vector2i mousePos);
    void render(sf::RenderWindow& window, std::map<int, Entity>& entities);
    void update(int id, std::map<int, Entity>& entities, UpdateType type,
                const std::any& value, int posId = 0);
};

} // namespace GameEngine
