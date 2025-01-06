/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Menu
*/

#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <System.hpp>
#include <components/Color.hpp>
#include <components/Link.hpp>
#include <components/OptionButton.hpp>
#include <components/Position.hpp>
#include <components/Shape.hpp>
#include <components/Slider.hpp>
#include <components/Sprite.hpp>
#include <components/Text.hpp>
#include <components/Texture.hpp>
#include <memory>
#include "menu/OptionMenu.hpp"

class Menu {
  public:
    Menu();
    ~Menu();
    void initMainMenu(std::map<int, GameEngine::Entity>& entities);
    void initLifeBar(std::map<int, GameEngine::Entity>& entities);
    void game(sf::RenderWindow& window, GameEngine::System system);

  protected:
  private:
};
