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
#include <components/Button.hpp>
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
    void initMainMenu(sf::RenderWindow& window, GameEngine::System system);
    void displayMenu(sf::RenderWindow& window, GameEngine::System system);
    GameEngine::Entity
    createEntityButton(int id, std::string title, std::string font,
                       int fontSize,
                       std::vector<std::pair<float, float>> position,
                       std::function<void()> callback);
    GameEngine::Entity
    createEntitySprite(int id, const std::pair<float, float> size,
                       std::string texture, std::vector<int> textureRect,
                       const std::vector<std::pair<float, float>> position);
    void isClickedPlay();
    void isClickedExit();

  private:
    std::map<int, GameEngine::Entity> _entitiesMenu;
    bool _entitiesInitialized = false;
    bool _canDisplay = true;
    enum class MenuState { MainMenu, OptionMenu };
    MenuState _currentMenuState = MenuState::MainMenu;
};
