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
    int _volumnMusic = 0;
    int _volumnGame = 0;
    int _resolution = 1;
    bool _adaptabilityText = false;
    float _elementSize = 0;
    bool _difficulty = false;
    bool _control = false;
    bool _constrast = false;
    bool _waitingForKey = false;
    HotkeysCodes _hotkeyPressed;
    std::map<HotkeysCodes, int> _hotkeyEntityMap;

  public:
    OptionMenu();
    ~OptionMenu();

    GameEngine::Entity
    createEntityText(int, const std::string,
                     const std::vector<std::pair<float, float>>, unsigned int);
    GameEngine::Entity
    createEntityOptionButton(int, std::vector<std::pair<float, float>>,
                             std::function<void()>);
    GameEngine::Entity
    createEntityButton(int id, std::string title, std::string font,
                       int fontSize,
                       std::vector<std::pair<float, float>> position,
                       std::function<void()> callback);
    GameEngine::Entity
    createEntitySlider(int, const std::pair<int, int>,
                        const std::vector<std::pair<float, float>>,
                        std::function<float()>, std::function<void(float)>);
    GameEngine::Entity
    createEntityRect(int id, const std::pair<int, int> size,
                        const std::vector<std::pair<float, float>> position,
                        sf::Color color, std::function<void()> callback);
    GameEngine::Entity
    createEntitySprite(int id, const std::pair<float, float> size,
                       std::string texture, std::vector<int> textureRect,
                       const std::vector<std::pair<float, float>> position);
    void displayOptionMenu(sf::RenderWindow&, GameEngine::System);
    void setNewKey(const sf::Event& event, GameEngine::System& system);
    int getVolumnMusic();
    void setVolumnMusic(int);
    int getVolumnGame();
    void setVolumnGame(int);
    int getResolution();
    void setResolution(int);
    bool getAdaptabilityText();
    void setAdaptabilityText();
    int getElementSize();
    void setElementSize(int);
    bool getDifficulty();
    void setDifficulty();
    bool getControl();
    void setControl();
    bool getContrast();
    void setContrast();
};