/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** This file declares the `Client` class, responsible for managing the
** client's entities and items in the game context. It allows for the
** creation, updating, and drawing of items as well as setting their
** properties like position, text, and sprites.
** Client.hpp
*/

#pragma once

#include <Entity.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <System.hpp>
#include <any>
#include <functional>
#include <iostream>
#include <memory>

class Client {
  private:
    std::map<int, std::map<std::string, std::any>> _items;
    std::map<int, std::map<std::string, std::any>> _updateItems;
    std::map<int, std::shared_ptr<GameEngine::Entity>> _entities;

  public:
    Client();
    ~Client();
    void manageClient();
    void manageBackground(GameEngine::System system, sf::Clock clock,
                          sf::Texture background);
};