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
#include "../../include/component/hotkey/HotkeysManager.hpp"
#include "Client.hpp"
#include "components/Button.hpp"
#include "components/Color.hpp"
#include "components/OptionButton.hpp"
#include "components/Position.hpp"
#include "components/Slider.hpp"
#include "components/Text.hpp"
#include "menu/Menu.hpp"
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

GameEngine::Entity OptionMenu::createEntityRect(
    int id, const std::pair<int, int> size,
    const std::vector<std::pair<float, float>> position, sf::Color color,
    std::function<void()> callback) {
    auto rectEntity = GameEngine::Entity(id);
    auto buttonRect = ButtonRect(size, color, true);
    buttonRect.setCallback(callback);
    rectEntity.addComponent(buttonRect);
    rectEntity.addComponent(Position(position));
    return rectEntity;
}

GameEngine::Entity
OptionMenu::createEntitySprite(int id, const std::pair<float, float> size,
                         std::string texture, std::vector<int> textureRect,
                         const std::vector<std::pair<float, float>> position) {
    auto newEntity = GameEngine::Entity(id);
    newEntity.addComponent(Sprite(size));
    newEntity.addComponent(Texture(texture, textureRect));
    newEntity.addComponent(Position(position));
    return newEntity;
}


void OptionMenu::setNewKey(const sf::Event& event, GameEngine::System& system) {
    if (_waitingForKey && event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key newKey = event.key.code;

        if (HotkeysManager::get().isKeyUsed(newKey)) {
            std::cout << "Already use" << std::endl;
            return;
        }

        HotkeysManager::get().setKey(_hotkeyPressed, newKey);
        _waitingForKey = false;

        if (_hotkeyEntityMap.find(_hotkeyPressed) != _hotkeyEntityMap.end()) {
            int entityId = _hotkeyEntityMap[_hotkeyPressed];
            system.update(entityId, _entitiesMenuOption,
                          GameEngine::UpdateType::Text,
                          HotkeysManager::get().keyToString(
                              HotkeysManager::get().getKey(_hotkeyPressed)));
        } else {
            std::cerr << "Error: Hotkey entity not found!" << std::endl;
        }
    }
}

void OptionMenu::displayOptionMenu(sf::RenderWindow& window,
                                   GameEngine::System system) {
    GetResponsiveValue responsive;
    int currentWidth = window.getSize().x;
    int currentHeight = window.getSize().y;
    if (!_entitiesInitialized) {
        int entityId = 0;
        _entitiesMenuOption.emplace( entityId,
            createEntitySprite( entityId++,
                {responsive.getResponsiveSizeX(800, currentWidth, 4),
                 responsive.getResponsiveSizeY(600, currentHeight, 4)},
                "assets/sprite/space.png", {0, 0, 400, 400},
                {{responsive.getResponsivePosX(800, currentWidth, 0),
                  responsive.getResponsivePosY(600, currentHeight,
                                               30)}}));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityButton(entityId++, "Back", "assets/font/Inter_Bold.ttf", 20, {{
                responsive.getResponsivePosX(800, currentWidth, 750),
                responsive.getResponsivePosY(600, currentHeight, 25)}}, [this]() { Menu::get().setMenuState(Menu::MenuState::MainMenu);}));
        _entitiesMenuOption.emplace(
            entityId, createEntityText(entityId++, "OPTIONS", {{
                responsive.getResponsivePosX(800, currentWidth, 340),
                responsive.getResponsivePosY(600, currentHeight, 10)}}, 45));

// Sound
        _entitiesMenuOption.emplace(
            entityId, createEntityText(entityId++, "Sound", {{
                responsive.getResponsivePosX(800, currentWidth, 40),
                responsive.getResponsivePosY(600, currentHeight, 100)}}, 20));
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, "Game effects", {{
                responsive.getResponsivePosX(800, currentWidth, 180),
                responsive.getResponsivePosY(600, currentHeight, 85)}}, 15));
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, std::to_string(getVolumnGame()), {{
                responsive.getResponsivePosX(800, currentWidth, 160),
                responsive.getResponsivePosY(600, currentHeight, 110)}}, 15));
        _entitiesMenuOption.emplace( entityId,
            createEntitySlider( entityId++, {0, 100}, {{
                responsive.getResponsivePosX(800, currentWidth, 180),
                responsive.getResponsivePosY(600, currentHeight, 115)}}, [this]() { return getVolumnMusic(); }, [this](int newValue) { setVolumnMusic(newValue); }));
        _entitiesMenuOption.emplace(
            entityId, createEntityText(entityId++, "Music", {{
                responsive.getResponsivePosX(800, currentWidth, 580),
                responsive.getResponsivePosY(600, currentHeight, 85)}}, 15));
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, std::to_string(getVolumnMusic()), {{
                responsive.getResponsivePosX(800, currentWidth, 560),
                responsive.getResponsivePosY(600, currentHeight, 110)}}, 15));
        _entitiesMenuOption.emplace( entityId,
            createEntitySlider( entityId++, {0, 100}, {{
                responsive.getResponsivePosX(800, currentWidth, 580),
                responsive.getResponsivePosY(600, currentHeight, 115)}}, [this]() { return (getVolumnGame()); }, [this](int newValue) { setVolumnGame(newValue); }));

// Key control
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, "Key control", {{
                responsive.getResponsivePosX(800, currentWidth, 40),
                responsive.getResponsivePosY(600, currentHeight, 170)}}, 20));
        _entitiesMenuOption.emplace(
            entityId, createEntityText(entityId++, HotkeysManager::get().keyToString(HotkeysManager::get().getKey(HotkeysCodes::ARROW_TOP)), {{
                responsive.getResponsivePosX(800, currentWidth, 160),
                responsive.getResponsivePosY(600, currentHeight, 170)}}, 20));
      
        _hotkeyEntityMap[HotkeysCodes::ARROW_TOP] = entityId;
        _entitiesMenuOption.emplace(
            entityId,
            createEntityRect(
                entityId++, {150, 50},
                {{responsive.getResponsivePosX(800, currentWidth, 155),
                  responsive.getResponsivePosY(600, currentHeight, 163)}},
                sf::Color::White, [this]() {
                    _waitingForKey = true;
                    _hotkeyPressed = HotkeysCodes::ARROW_TOP;
                }));

        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++,
                HotkeysManager::get().keyToString(
                    HotkeysManager::get().getKey(HotkeysCodes::ARROW_BOTTOM)),
                {{responsive.getResponsivePosX(800, currentWidth, 260),
                  responsive.getResponsivePosY(600, currentHeight, 170)}},
                20));
        _hotkeyEntityMap[HotkeysCodes::ARROW_BOTTOM] = entityId;
        _entitiesMenuOption.emplace(
            entityId,
            createEntityRect(
                entityId++, {150, 50},
                {{responsive.getResponsivePosX(800, currentWidth, 255),
                  responsive.getResponsivePosY(600, currentHeight, 163)}},
                sf::Color::White, [this]() {
                    _waitingForKey = true;
                    _hotkeyPressed = HotkeysCodes::ARROW_BOTTOM;
                }));

        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++,
                HotkeysManager::get().keyToString(
                    HotkeysManager::get().getKey(HotkeysCodes::ARROW_LEFT)),
                {{responsive.getResponsivePosX(800, currentWidth, 360),
                  responsive.getResponsivePosY(600, currentHeight, 170)}},
                20));
        _hotkeyEntityMap[HotkeysCodes::ARROW_LEFT] = entityId;
        _entitiesMenuOption.emplace(
            entityId,
            createEntityRect(
                entityId++, {150, 50},
                {{responsive.getResponsivePosX(800, currentWidth, 355),
                  responsive.getResponsivePosY(600, currentHeight, 163)}},
                sf::Color::White, [this]() {
                    _waitingForKey = true;
                    _hotkeyPressed = HotkeysCodes::ARROW_LEFT;
                }));

        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++,
                HotkeysManager::get().keyToString(
                    HotkeysManager::get().getKey(HotkeysCodes::ARROW_RIGHT)),
                {{responsive.getResponsivePosX(800, currentWidth, 460),
                  responsive.getResponsivePosY(600, currentHeight, 170)}},
                20));
        _hotkeyEntityMap[HotkeysCodes::ARROW_RIGHT] = entityId;
        _entitiesMenuOption.emplace(
            entityId,
            createEntityRect(
                entityId++, {150, 50},
                {{responsive.getResponsivePosX(800, currentWidth, 455),
                  responsive.getResponsivePosY(600, currentHeight, 163)}},
                sf::Color::White, [this]() {
                    _waitingForKey = true;
                    _hotkeyPressed = HotkeysCodes::ARROW_RIGHT;
                }));

        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++,
                HotkeysManager::get().keyToString(
                    HotkeysManager::get().getKey(HotkeysCodes::ENTER)),
                {{responsive.getResponsivePosX(800, currentWidth, 560),
                  responsive.getResponsivePosY(600, currentHeight, 170)}},
                20));
        _hotkeyEntityMap[HotkeysCodes::ENTER] = entityId;
        _entitiesMenuOption.emplace(
            entityId,
            createEntityRect(
                entityId++, {150, 50},
                {{responsive.getResponsivePosX(800, currentWidth, 555),
                  responsive.getResponsivePosY(600, currentHeight, 163)}},
                sf::Color::White, [this]() {
                    _waitingForKey = true;
                    _hotkeyPressed = HotkeysCodes::ENTER;
                }));

        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++,
                HotkeysManager::get().keyToString(
                    HotkeysManager::get().getKey(HotkeysCodes::SPACE)),
                {{responsive.getResponsivePosX(800, currentWidth, 660),
                  responsive.getResponsivePosY(600, currentHeight, 170)}},
                20));
        _hotkeyEntityMap[HotkeysCodes::SPACE] = entityId;
        _entitiesMenuOption.emplace(
            entityId,
            createEntityRect(
                entityId++, {150, 50},
                {{responsive.getResponsivePosX(800, currentWidth, 655),
                  responsive.getResponsivePosY(600, currentHeight, 163)}},
                sf::Color::White, [this]() {
                    _waitingForKey = true;
                    _hotkeyPressed = HotkeysCodes::SPACE;
                }));

        // Adaptability
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, "Font for people with reading difficulties",
                {{responsive.getResponsivePosX(800, currentWidth, 40),
                  responsive.getResponsivePosY(600, currentHeight, 240)}},
                20));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityOptionButton(
                entityId++,
                {{responsive.getResponsivePosX(800, currentWidth, 720),
                  responsive.getResponsivePosY(600, currentHeight, 240)}},
                [this]() { setAdaptabilityText(); }));

        // Size of elements
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
                entityId++, "Enlarge",
                {{responsive.getResponsivePosX(800, currentWidth, 580),
                  responsive.getResponsivePosY(600, currentHeight, 280)}},
                15));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, std::to_string(getElementSize()),
                {{responsive.getResponsivePosX(800, currentWidth, 560),
                  responsive.getResponsivePosY(600, currentHeight, 305)}},
                15));
        _entitiesMenuOption.emplace(
            entityId,
            createEntitySlider(
                entityId++, {0, 100},
                {{responsive.getResponsivePosX(800, currentWidth, 580),
                  responsive.getResponsivePosY(600, currentHeight, 310)}},
                [this]() { return getElementSize(); },
                [this](int newValue) { setElementSize(newValue); }));

        // Contrast
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, "High contrast",
                {{responsive.getResponsivePosX(800, currentWidth, 40),
                  responsive.getResponsivePosY(600, currentHeight, 380)}},
                20));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityOptionButton(
                entityId++,
                {{responsive.getResponsivePosX(800, currentWidth, 720),
                  responsive.getResponsivePosY(600, currentHeight, 380)}},
                [this]() { setContrast(); }));

        // Difficulty
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, "High difficulty",
                {{responsive.getResponsivePosX(800, currentWidth, 40),
                  responsive.getResponsivePosY(600, currentHeight, 450)}},
                20));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityOptionButton(
                entityId++,
                {{responsive.getResponsivePosX(800, currentWidth, 720),
                  responsive.getResponsivePosY(600, currentHeight, 450)}},
                [this]() { setDifficulty(); }));

        // Controller
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
                  responsive.getResponsivePosY(600, currentHeight, 520)}},
                [this]() { setControl(); }));
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
int OptionMenu::getElementSize() {
    return _elementSize;
}

void OptionMenu::setElementSize(int new_size) {
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