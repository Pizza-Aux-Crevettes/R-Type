/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** OptionMenu.cpp
*/

#include "menu/OptionMenu.hpp"
#include <Entity.hpp>
#include <SFML/Graphics.hpp>
#include <iomanip>
#include "Client.hpp"
#include "components/Button.hpp"
#include "components/Color.hpp"
#include "components/OptionButton.hpp"
#include "components/Position.hpp"
#include "components/Slider.hpp"
#include "components/Text.hpp"
#include "util/getResponsiveValue.hpp"

OptionMenu::OptionMenu() {}

OptionMenu::~OptionMenu() {}

GameEngine::Entity OptionMenu::createEntityText(
    int id, const std::string text,
    const std::vector<std::pair<float, float>> position,
    unsigned int fontSize) {
    auto newEntity = GameEngine::Entity(id);
    newEntity.addComponent(Text(text, "assets/font/Inter_Bold.ttf", fontSize));
    newEntity.addComponent(Position(position));
    newEntity.addComponent(Color({255, 255, 255, 255}));
    return newEntity;
}

GameEngine::Entity OptionMenu::createEntityOptionButton(
    int id, std::vector<std::pair<float, float>> position,
    std::function<void()> callback) {
    auto newEntity = GameEngine::Entity(id);
    auto button = OptionButton({20, 20});
    button.setCallback(callback);
    newEntity.addComponent(button);
    newEntity.addComponent(Position(position));
    newEntity.addComponent(Color({255, 255, 255, 255}));
    return newEntity;
}

GameEngine::Entity
OptionMenu::createEntityButton(int id, std::string title, std::string font,
                               int fontSize,
                               std::vector<std::pair<float, float>> position,
                               std::function<void()> callback) {
    auto newEntity = GameEngine::Entity(id);
    auto button = Button(title, font, fontSize);
    button.setCallback(callback);
    newEntity.addComponent(button);
    newEntity.addComponent(Position(position));
    newEntity.addComponent(Color({255, 255, 255, 255}));
    return newEntity;
}

GameEngine::Entity OptionMenu::createEntitySlider(
    int id, const std::pair<int, int> values,
    const std::vector<std::pair<float, float>> position,
    std::function<float()> getter, std::function<void(float)> setter) {
    auto newEntity = GameEngine::Entity(id);
    auto slider = Slider(values, {200, 3});
    slider.setGetCallback(getter);
    slider.setSetCallback(setter);
    newEntity.addComponent(slider);
    newEntity.addComponent(Position(position));
    newEntity.addComponent(Color({255, 255, 255, 255}));
    return newEntity;
}

void OptionMenu::printExit() {
    std::cout << "Exit clicked" << std::endl;
}

void OptionMenu::displayOptionMenu(sf::RenderWindow& window,
                                   GameEngine::System system) {
    GetResponsiveValue responsive;
    int currentWidth = window.getSize().x;
    int currentHeight = window.getSize().y;
    if (!_entitiesInitialized) {
        int entityId = 0;
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, "OPTIONS",
                {{responsive.getResponsivePosX(800, currentWidth, 300),
                  responsive.getResponsivePosY(600, currentHeight, 10)}},
                45));
        entityId,
            createEntityButton(
                entityId++, "Exit", "assets/font/Inter_Bold.ttf", 20,
                {{responsive.getResponsivePosX(1920, currentWidth, 900),
                  responsive.getResponsivePosY(10780, currentWidth, 500)}},
                [this]() { printExit(); });
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, "Sound",
                {{responsive.getResponsivePosX(800, currentWidth, 40),
                  responsive.getResponsivePosY(600, currentHeight, 100)}},
                20));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, "Key control",
                {{responsive.getResponsivePosX(800, currentWidth, 40),
                  responsive.getResponsivePosY(600, currentHeight, 170)}},
                20));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, "Font for people with reading difficulties",
                {{responsive.getResponsivePosX(800, currentWidth, 40),
                  responsive.getResponsivePosY(600, currentHeight, 240)}},
                20));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, "Size of elements",
                {{responsive.getResponsivePosX(800, currentWidth, 40),
                  responsive.getResponsivePosY(600, currentHeight, 310)}},
                20));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, "High contrast",
                {{responsive.getResponsivePosX(800, currentWidth, 40),
                  responsive.getResponsivePosY(600, currentHeight, 380)}},
                20));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, "High difficulty",
                {{responsive.getResponsivePosX(800, currentWidth, 40),
                  responsive.getResponsivePosY(600, currentHeight, 450)}},
                20));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, "Controller  mode",
                {{responsive.getResponsivePosX(800, currentWidth, 40),
                  responsive.getResponsivePosY(600, currentHeight, 520)}},
                20));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityOptionButton(
                entityId++,
                {{responsive.getResponsivePosX(800, currentWidth, 720),
                  responsive.getResponsivePosY(600, currentHeight, 240)}},
                [this]() { setAdaptabilityText(); }));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityOptionButton(
                entityId++,
                {{responsive.getResponsivePosX(800, currentWidth, 720),
                  responsive.getResponsivePosY(600, currentHeight, 380)}},
                [this]() { setContrast(); }));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityOptionButton(
                entityId++,
                {{responsive.getResponsivePosX(800, currentWidth, 720),
                  responsive.getResponsivePosY(600, currentHeight, 450)}},
                [this]() { setDifficulty(); }));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityOptionButton(
                entityId++,
                {{responsive.getResponsivePosX(800, currentWidth, 720),
                  responsive.getResponsivePosY(600, currentHeight, 170)}},
                [this]() { setControl(); }));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, "Game effects",
                {{responsive.getResponsivePosX(800, currentWidth, 160),
                  responsive.getResponsivePosY(600, currentHeight, 105)}},
                15));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, std::to_string(getVolumnGame()),
                {{responsive.getResponsivePosX(800, currentWidth, 140),
                  responsive.getResponsivePosY(600, currentHeight, 105)}},
                15));
        _entitiesMenuOption.emplace(
            entityId,
            createEntitySlider(
                entityId++, {0, 100},
                {{responsive.getResponsivePosX(800, currentWidth, 160),
                  responsive.getResponsivePosY(600, currentHeight, 115)}},
                [this]() { return static_cast<float>(getVolumnMusic()); },
                [this](float newValue) {
                    setVolumnMusic(static_cast<int>(newValue));
                }));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, "Music",
                {{responsive.getResponsivePosX(800, currentWidth, 545),
                  responsive.getResponsivePosY(600, currentHeight, 105)}},
                15));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, std::to_string(getVolumnMusic()),
                {{responsive.getResponsivePosX(800, currentWidth, 525),
                  responsive.getResponsivePosY(600, currentHeight, 105)}},
                15));
        _entitiesMenuOption.emplace(
            entityId,
            createEntitySlider(
                entityId++, {0, 100},
                {{responsive.getResponsivePosX(800, currentWidth, 545),
                  responsive.getResponsivePosY(600, currentHeight, 115)}},
                [this]() { return static_cast<float>(getVolumnGame()); },
                [this](float newValue) {
                    setVolumnGame(static_cast<int>(newValue));
                }));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, "Enlarge",
                {{responsive.getResponsivePosX(800, currentWidth, 545),
                  responsive.getResponsivePosY(600, currentHeight, 280)}},
                15));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, std::to_string(getElementSize()),
                {{responsive.getResponsivePosX(800, currentWidth, 525),
                  responsive.getResponsivePosY(600, currentHeight, 300)}},
                15));
        _entitiesMenuOption.emplace(
            entityId,
            createEntitySlider(
                entityId++, {0, 2},
                {{responsive.getResponsivePosX(800, currentWidth, 545),
                  responsive.getResponsivePosY(600, currentHeight, 310)}},
                [this]() { return static_cast<float>(getElementSize()); },
                [this](float newValue) { setElementSize(newValue); }));
        _entitiesInitialized = true;
    }
    system.render(window, _entitiesMenuOption);
}

// Volumn music
int OptionMenu::getVolumnMusic() {
    return _volumnMusic;
}

void OptionMenu::setVolumnMusic(int new_volumn) {
    _volumnMusic = new_volumn;
    std::cout << "New volumn music " << _volumnMusic << std::endl;
}

// Volumn game
int OptionMenu::getVolumnGame() {
    return _volumnGame;
}

void OptionMenu::setVolumnGame(int new_volumn) {
    _volumnGame = new_volumn;
    std::cout << "New volumn game " << _volumnGame << std::endl;
}

// Resolution
int OptionMenu::getResolution() {
    return _resolution;
}

void OptionMenu::setResolution(int new_resolution) {
    _resolution = new_resolution;
    std::cout << "New resolution " << _resolution << std::endl;
}

// Adaptability text
bool OptionMenu::getAdaptabilityText() {
    return _adaptabilityText;
}

void OptionMenu::setAdaptabilityText() {
    _adaptabilityText = !_adaptabilityText;
    std::cout << "New adaptability state " << _adaptabilityText << std::endl;
}

// Element size
float OptionMenu::getElementSize() {
    return _elementSize;
}

void OptionMenu::setElementSize(float new_size) {
    _elementSize = new_size;
    std::cout << "New element size " << _elementSize << std::endl;
}

// Difficulty : false = normal && true = difficult
bool OptionMenu::getDifficulty() {
    return _difficulty;
}

void OptionMenu::setDifficulty() {
    _difficulty = !_difficulty;
    std::cout << "New difficulty state " << _difficulty << std::endl;
}

// Control : false = keyboard && true = controller
bool OptionMenu::getControl() {
    return _control;
}

void OptionMenu::setControl() {
    _control = !_control;
    std::cout << "New control state " << _control << std::endl;
}

// Contrast : false = disabled && true = enabled
bool OptionMenu::getContrast() {
    return _constrast;
}

void OptionMenu::setContrast() {
    _constrast = !_constrast;
    std::cout << "New contrast state " << _constrast << std::endl;
}