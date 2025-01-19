/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** OptionMenu.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <System.hpp>
#include <functional>
#include <memory>
#include "component/hotkey/HotkeysCodes.hpp"

class OptionMenu {
  private:
    std::map<int, GameEngine::Entity> _entitiesMenuOption;
    bool _entitiesInitialized = false;
    int _volumnMusic = 100;
    int _volumnGame = 100;
    std::string _fontFile = "assets/font/Inter_Bold.ttf";
    unsigned int _fontSize = 100;
    bool _waitingForKey = false;
    HotkeysCodes _hotkeyPressed;
    std::map<HotkeysCodes, int> _hotkeyEntityMap;

  public:
    OptionMenu();
    ~OptionMenu();
  
    static OptionMenu& get();

    GameEngine::Entity
    createEntityText(int, std::string title,
                     const std::vector<std::pair<float, float>>, unsigned int);
    GameEngine::Entity
    createEntityOptionButton(int, std::vector<std::pair<float, float>>,
                             std::function<void()>);
    GameEngine::Entity
    createEntitySlider(int id, float current, const std::pair<int, int> values,
                        const std::vector<std::pair<float, float>> position,
                        std::function<void(float)> callback);
    GameEngine::Entity
    createEntityRect(int id, const std::pair<int, int> size,
                        const std::vector<std::pair<float, float>> position,
                        sf::Color color, std::function<void()> callback);
    GameEngine::Entity
    createEntitySprite(int id, const std::pair<float, float> size,
                       std::string texture, std::vector<int> textureRect,
                       const std::vector<std::pair<float, float>> position);
    void displayOptionMenu(sf::RenderWindow&, GameEngine::System, std::map<int, GameEngine::Entity> entities);

    void setNewKey(const sf::Event& event, GameEngine::System& system);

    int getVolumnMusic();
    void setVolumnMusic(int);

    int getVolumnGame();
    void setVolumnGame(int);

    std::string getAdaptabilityText();
    void setAdaptabilityText(GameEngine::System& system, std::map<int, GameEngine::Entity> entities);

    int getFontSize();
    void setFontSize(unsigned int new_size, GameEngine::System& system, std::map<int, GameEngine::Entity> entities);
};