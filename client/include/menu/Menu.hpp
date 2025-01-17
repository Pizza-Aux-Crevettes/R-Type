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
#include <components/Button.hpp>
#include <components/ButtonRect.hpp>
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
    enum class MenuState { MainMenu, OptionMenu };

    Menu();
    ~Menu();

    static Menu& get();

    void initMainMenu(sf::RenderWindow& window, GameEngine::System system);
    void displayMenu(sf::RenderWindow& window, GameEngine::System system,
                     OptionMenu& optionMenu);
    GameEngine::Entity
    createEntitySprite(int id, const std::pair<float, float> size,
                       std::string texture, std::vector<int> textureRect,
                       const std::vector<std::pair<float, float>> position);
    GameEngine::Entity
    createEntityRect(int id, const std::pair<int, int> size,
                     const std::vector<std::pair<float, float>> position,
                     sf::Color color, std::function<void()> callback);
    void setMenuState(MenuState state);
    GameEngine::Entity
    createEntityInput(int id, std::string font, int fontSize,
                      const std::vector<std::pair<float, float>> position,
                      std::string inputVar);
    GameEngine::Entity createEntityText(
                      int id, const std::string text,
                      const std::vector<std::pair<float, float>> position,
                      unsigned int fontSize);

    void isClickedInput(bool isIpClicked, bool isPortClicked,
                        bool isUsernameClicked);
    void setupInput(const sf::Event& event);

  private:
    std::map<int, GameEngine::Entity> _entitiesMenu;
    bool _entitiesInitialized = false;
    bool _canDisplay = true;
    MenuState _currentMenuState = MenuState::MainMenu;
    bool _isIpClicked;
    bool _isPortClicked;
    bool _isUsernameClicked;
    int _ipId;
    int _usernameId;
};
