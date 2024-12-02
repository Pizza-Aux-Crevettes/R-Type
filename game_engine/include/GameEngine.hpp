/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** GameEngine.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
class GameEngine {
  private:
    sf::RenderWindow _window;

  public:
    GameEngine();
    ~GameEngine();
    void manageEntity();
    void createWindow();
    void destroyWindow();
    void manageSystem();
};