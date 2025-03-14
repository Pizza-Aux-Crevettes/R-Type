/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** This file contains the implementation of the OptionMenu class, responsible
** for managing and displaying the options menu in the game. It includes
** functionalities like setting key bindings, adjusting volume, controlling 
** game resolution, enabling or disabling contrast, and controlling game difficulty.
** OptionMenu.cpp
*/

#include "menu/OptionMenu.hpp"
#include <Entity.hpp>
#include <SFML/Graphics.hpp>
#include <iomanip>
#include "component/hotkey/HotkeysManager.hpp"
#include "component/sound/SoundManager.hpp"
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

OptionMenu& OptionMenu::get() {
    static OptionMenu instance;
    return instance;
}

GameEngine::Entity OptionMenu::createEntityText(
    int id, const std::string text,
    const std::vector<std::pair<float, float>> position,
    unsigned int fontSize) {
    auto newEntity = GameEngine::Entity(id);
    newEntity.addComponent(Text(text, _fontFile, fontSize));
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

GameEngine::Entity OptionMenu::createEntitySlider(
    int id, float current, const std::pair<int, int> values,
    const std::vector<std::pair<float, float>> position, 
    std::function<void(float)> callback) {
    auto newEntity = GameEngine::Entity(id);
    auto slider = Slider(current, values, {200, 3});
    slider.setCallback(callback);
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
                                   GameEngine::System system, std::map<int, GameEngine::Entity> entities) {
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
            createEntityRect(
                entityId++, {55, 22},
                {{responsive.getResponsivePosX(800, currentWidth, 748),
                  responsive.getResponsivePosY(600, currentHeight, 32)}},
                sf::Color::Transparent, [this]() { Menu::get().setMenuState(Menu::MenuState::MainMenu);}));

        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(entityId++, "Back", {{
                responsive.getResponsivePosX(800, currentWidth, 765),
                responsive.getResponsivePosY(600, currentHeight, 35)}}, 20));
        _entitiesMenuOption.emplace(
            entityId, createEntityText(entityId++, "OPTIONS", {{
                responsive.getResponsivePosX(800, currentWidth, 400),
                responsive.getResponsivePosY(600, currentHeight, 35)}}, 45));

// Sound
        _entitiesMenuOption.emplace(
            entityId, createEntityText(entityId++, "Sound", {{
                responsive.getResponsivePosX(800, currentWidth, 55),
                responsive.getResponsivePosY(600, currentHeight, 130)}}, 20));
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, "Game effects", {{
                responsive.getResponsivePosX(800, currentWidth, 210),
                responsive.getResponsivePosY(600, currentHeight, 100)}}, 15));
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, std::to_string(getVolumnGame()), {{
                responsive.getResponsivePosX(800, currentWidth, 160),
                responsive.getResponsivePosY(600, currentHeight, 125)}}, 15));
        _entitiesMenuOption.emplace( entityId,
            createEntitySlider( entityId++, 100, {0, 100}, {{
                responsive.getResponsivePosX(800, currentWidth, 180),
                responsive.getResponsivePosY(600, currentHeight, 130)}},
                [this](int newValue) { setVolumnGame(newValue);}));
        _entitiesMenuOption.emplace(
            entityId, createEntityText(entityId++, "Music", {{
                responsive.getResponsivePosX(800, currentWidth, 595),
                responsive.getResponsivePosY(600, currentHeight, 100)}}, 15));
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, std::to_string(getVolumnMusic()), {{
                responsive.getResponsivePosX(800, currentWidth, 560),
                responsive.getResponsivePosY(600, currentHeight, 125)}}, 15));
        _entitiesMenuOption.emplace( entityId,
            createEntitySlider( entityId++, 100, {0, 100}, {{
                responsive.getResponsivePosX(800, currentWidth, 580),
                responsive.getResponsivePosY(600, currentHeight, 130)}},
                [this](int newValue) { setVolumnMusic(newValue); }));

// Key control
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, "Key control", {{
                responsive.getResponsivePosX(800, currentWidth, 60),
                responsive.getResponsivePosY(600, currentHeight, 250)}}, 20));

        _entitiesMenuOption.emplace(
            entityId, createEntityText(entityId++, HotkeysManager::get().keyToString(HotkeysManager::get().getKey(HotkeysCodes::ARROW_TOP)), {{
                responsive.getResponsivePosX(800, currentWidth, 200),
                responsive.getResponsivePosY(600, currentHeight, 250)}}, 20));
        _hotkeyEntityMap[HotkeysCodes::ARROW_TOP] = entityId;
        _entitiesMenuOption.emplace(
            entityId,
            createEntityRect(
                entityId++, {150, 50},
                {{responsive.getResponsivePosX(800, currentWidth, 155),
                  responsive.getResponsivePosY(600, currentHeight, 233)}},
                sf::Color::White, [this]() {
                    _waitingForKey = true;
                    _hotkeyPressed = HotkeysCodes::ARROW_TOP;
                }));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++,
                "Move up",
                {{responsive.getResponsivePosX(800, currentWidth, 200),
                  responsive.getResponsivePosY(600, currentHeight, 295)}},
                15));

        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++,
                HotkeysManager::get().keyToString(
                    HotkeysManager::get().getKey(HotkeysCodes::ARROW_BOTTOM)),
                {{responsive.getResponsivePosX(800, currentWidth, 300),
                  responsive.getResponsivePosY(600, currentHeight, 250)}},
                20));
        _hotkeyEntityMap[HotkeysCodes::ARROW_BOTTOM] = entityId;
        _entitiesMenuOption.emplace(
            entityId,
            createEntityRect(
                entityId++, {150, 50},
                {{responsive.getResponsivePosX(800, currentWidth, 255),
                  responsive.getResponsivePosY(600, currentHeight, 233)}},
                sf::Color::White, [this]() {
                    _waitingForKey = true;
                    _hotkeyPressed = HotkeysCodes::ARROW_BOTTOM;
                }));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++,
                "Move down",
                {{responsive.getResponsivePosX(800, currentWidth, 300),
                  responsive.getResponsivePosY(600, currentHeight, 295)}},
                15));

        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++,
                HotkeysManager::get().keyToString(
                    HotkeysManager::get().getKey(HotkeysCodes::ARROW_LEFT)),
                {{responsive.getResponsivePosX(800, currentWidth, 400),
                  responsive.getResponsivePosY(600, currentHeight, 250)}},
                20));
        _hotkeyEntityMap[HotkeysCodes::ARROW_LEFT] = entityId;
        _entitiesMenuOption.emplace(
            entityId,
            createEntityRect(
                entityId++, {150, 50},
                {{responsive.getResponsivePosX(800, currentWidth, 355),
                  responsive.getResponsivePosY(600, currentHeight, 233)}},
                sf::Color::White, [this]() {
                    _waitingForKey = true;
                    _hotkeyPressed = HotkeysCodes::ARROW_LEFT;
                }));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++,
                "Move left",
                {{responsive.getResponsivePosX(800, currentWidth, 400),
                  responsive.getResponsivePosY(600, currentHeight, 295)}},
                15));

        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++,
                HotkeysManager::get().keyToString(
                    HotkeysManager::get().getKey(HotkeysCodes::ARROW_RIGHT)),
                {{responsive.getResponsivePosX(800, currentWidth, 500),
                  responsive.getResponsivePosY(600, currentHeight, 250)}},
                20));
        _hotkeyEntityMap[HotkeysCodes::ARROW_RIGHT] = entityId;
        _entitiesMenuOption.emplace(
            entityId,
            createEntityRect(
                entityId++, {150, 50},
                {{responsive.getResponsivePosX(800, currentWidth, 455),
                  responsive.getResponsivePosY(600, currentHeight, 233)}},
                sf::Color::White, [this]() {
                    _waitingForKey = true;
                    _hotkeyPressed = HotkeysCodes::ARROW_RIGHT;
                }));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++,
                "Move right",
                {{responsive.getResponsivePosX(800, currentWidth, 500),
                  responsive.getResponsivePosY(600, currentHeight, 295)}},
                15));

        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++,
                HotkeysManager::get().keyToString(
                    HotkeysManager::get().getKey(HotkeysCodes::ENTER)),
                {{responsive.getResponsivePosX(800, currentWidth, 600),
                  responsive.getResponsivePosY(600, currentHeight, 250)}},
                20));
        _hotkeyEntityMap[HotkeysCodes::ENTER] = entityId;
        _entitiesMenuOption.emplace(
            entityId,
            createEntityRect(
                entityId++, {150, 50},
                {{responsive.getResponsivePosX(800, currentWidth, 555),
                  responsive.getResponsivePosY(600, currentHeight, 233)}},
                sf::Color::White, [this]() {
                    _waitingForKey = true;
                    _hotkeyPressed = HotkeysCodes::ENTER;
                }));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++,
                "Auto-fire",
                {{responsive.getResponsivePosX(800, currentWidth, 600),
                  responsive.getResponsivePosY(600, currentHeight, 295)}},
                15));

        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++,
                HotkeysManager::get().keyToString(
                    HotkeysManager::get().getKey(HotkeysCodes::SPACE)),
                {{responsive.getResponsivePosX(800, currentWidth, 700),
                  responsive.getResponsivePosY(600, currentHeight, 250)}},
                20));
        _hotkeyEntityMap[HotkeysCodes::SPACE] = entityId;
        _entitiesMenuOption.emplace(
            entityId,
            createEntityRect(
                entityId++, {150, 50},
                {{responsive.getResponsivePosX(800, currentWidth, 655),
                  responsive.getResponsivePosY(600, currentHeight, 233)}},
                sf::Color::White, [this]() {
                    _waitingForKey = true;
                    _hotkeyPressed = HotkeysCodes::SPACE;
                }));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++,
                "Shoot",
                {{responsive.getResponsivePosX(800, currentWidth, 700),
                  responsive.getResponsivePosY(600, currentHeight, 295)}},
                15));
                
        // Adaptability
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, "Dyslexic font",
                {{responsive.getResponsivePosX(800, currentWidth, 63),
                  responsive.getResponsivePosY(600, currentHeight, 375)}},
                20));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityOptionButton(
                entityId++,
                {{responsive.getResponsivePosX(800, currentWidth, 720),
                  responsive.getResponsivePosY(600, currentHeight, 375)}},
                [this, &system, &entities]() { setAdaptabilityText(system, entities);}));

        // Fonts size
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, "Font size",
                {{responsive.getResponsivePosX(800, currentWidth, 60),
                  responsive.getResponsivePosY(600, currentHeight, 490)}},
                20));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, "Enlarge",
                {{responsive.getResponsivePosX(800, currentWidth, 595),
                  responsive.getResponsivePosY(600, currentHeight, 460)}},
                15));
        _entitiesMenuOption.emplace(
            entityId,
            createEntityText(
                entityId++, std::to_string(getFontSize()),
                {{responsive.getResponsivePosX(800, currentWidth, 560),
                  responsive.getResponsivePosY(600, currentHeight, 485)}},
                15));
        _entitiesMenuOption.emplace(
            entityId,
            createEntitySlider(
                entityId++, 100, {50, 150},
                {{responsive.getResponsivePosX(800, currentWidth, 580),
                  responsive.getResponsivePosY(600, currentHeight, 490)}},
                [this, &system, &entities](int newValue) { setFontSize(newValue, system, entities); }));
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
    SoundManager::get().setMusicVolumn(_volumnMusic);
}

// Volumn game
int OptionMenu::getVolumnGame() {
    return _volumnGame;
}

void OptionMenu::setVolumnGame(int new_volumn) {
    _volumnGame = new_volumn;
    SoundManager::get().setEffectVolumn(_volumnGame);
}

// Adaptability text
std::string OptionMenu::getAdaptabilityText() {
    return _fontFile;
}

void OptionMenu::setAdaptabilityText(GameEngine::System& system, std::map<int, GameEngine::Entity> entities) {
    if (_fontFile == "assets/font/Inter_Bold.ttf") {
        _fontFile = "assets/font/open-dyslexic.ttf";
    } else {
        _fontFile = "assets/font/Inter_Bold.ttf";
    };
    for (auto& [id, entity] : _entitiesMenuOption) {
        if (entity.hasComponent<Text>()) {
            system.update(id, _entitiesMenuOption, GameEngine::UpdateType::TextFont, _fontFile);
        }
    }
    for (auto& [id, entity] : entities) {
        if (entity.hasComponent<Text>()) {
            system.update(id, entities, GameEngine::UpdateType::TextFont, _fontFile);
        }
    }
}

// Font size
int OptionMenu::getFontSize() {
    return _fontSize;
}

void OptionMenu::setFontSize(unsigned int new_size, GameEngine::System& system, std::map<int, GameEngine::Entity> entities) {
    _fontSize = new_size;
    for (auto& [id, entity] : _entitiesMenuOption) {
        if (entity.hasComponent<Text>()) {
            system.update(id, _entitiesMenuOption, GameEngine::UpdateType::TextSize, _fontSize);
        }
    }
    for (auto& [id, entity] : entities) {
        if (entity.hasComponent<Text>()) {
            system.update(id, entities, GameEngine::UpdateType::TextSize, _fontSize);
        }
    }
}
