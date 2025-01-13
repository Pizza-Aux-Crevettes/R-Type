/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** OptionMenu.cpp
*/

#include "menu/OptionMenu.hpp"
#include "menu/Menu.hpp"
#include <Entity.hpp>
#include <SFML/Graphics.hpp>
#include <iomanip>
#include "Client.hpp"
#include "../../include/component/hotkey/HotkeysManager.hpp"
#include "components/Button.hpp"
#include "components/Color.hpp"
#include "components/OptionButton.hpp"
#include "components/Position.hpp"
#include "components/Slider.hpp"
#include "components/Text.hpp"

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
    auto button = Button("", font, fontSize);
    button.setCallback(callback);
    newEntity.addComponent(button);
    newEntity.addComponent(Position(position));
    newEntity.addComponent(Text(title, "assets/font/Inter_Bold.ttf", 20));
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

GameEngine::Entity
OptionMenu::createEntityRect(int id, const std::pair<int, int> size, const std::vector<std::pair<float, float>> position, sf::Color color, std::function<void()> callback) {
    auto rectEntity = GameEngine::Entity(id);
    auto buttonRect = ButtonRect(size, color);
    buttonRect.setCallback(callback);
    rectEntity.addComponent(buttonRect);
    rectEntity.addComponent(Position(position));
    return rectEntity;
}

void OptionMenu::setNewKey(const sf::Event& event, GameEngine::System& system) {
    if (_waitingForKey && event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key newKey = event.key.code;

        if (HotkeysManager::get().isKeyUsed(newKey)) {
            std::cout << "Already use" << std::endl;
            return;
        }

        HotkeysManager::get().setKey(_hotkeyPressed, newKey);
        std::cout << "New : " << HotkeysManager::get().keyToString(HotkeysManager::get().getKey(_hotkeyPressed)) << std::endl;
        _waitingForKey = false;

        if (_hotkeyEntityMap.find(_hotkeyPressed) != _hotkeyEntityMap.end()) {
            int entityId = _hotkeyEntityMap[_hotkeyPressed];
            std::cout << "entity id " << entityId << std::endl;
            system.update(entityId, _entitiesMenuOption, GameEngine::UpdateType::Text, HotkeysManager::get().keyToString(newKey));
            std::cout << "system update text" << std::endl;

        } else {
            std::cerr << "Error: Hotkey entity not found!" << std::endl;
        }
    }
}

void isClickedExit() {
    std::cout << "Button Exit clicked!" << std::endl;
}

void OptionMenu::displayOptionMenu(sf::RenderWindow& window,
                                   GameEngine::System system) {
    if (!_entitiesInitialized) {
        int entityId = 0;
        _entitiesMenuOption.emplace(
            entityId,
            createEntityButton(entityId++, "Exit", "assets/font/Inter_Bold.ttf",
                               20, {{750, 50}}, [this]() { isClickedExit();
                               Menu::get().setMenuState(Menu::MenuState::MainMenu); }));
                            //    20, {{750, 50}}, [this]() { Menu::get().setMenuState(Menu::MenuState::MainMenu); }));
        _entitiesMenuOption.emplace(
            entityId, createEntityText(entityId++, "OPTIONS", {{300, 10}}, 45));
// Sound
        _entitiesMenuOption.emplace(
            entityId, createEntityText(entityId++, "Sound", {{40, 100}}, 20));
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, "Game effects", {{160, 85}}, 15));
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, std::to_string(getVolumnGame()), {{130, 105}}, 15));
        _entitiesMenuOption.emplace( entityId,
            createEntitySlider( entityId++, {0, 100}, {{155, 115}}, [this]() { return getVolumnMusic(); }, [this](int newValue) { setVolumnMusic(newValue); }));
        _entitiesMenuOption.emplace(
            entityId, createEntityText(entityId++, "Music", {{545, 85}}, 15));
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, std::to_string(getVolumnMusic()), {{520, 105}}, 15));
        _entitiesMenuOption.emplace( entityId,
            createEntitySlider( entityId++, {0, 100}, {{545, 115}}, [this]() { return (getVolumnGame()); }, [this](int newValue) { setVolumnGame(newValue); }));

// Key control
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, "Key control", {{40, 170}}, 20));
        _entitiesMenuOption.emplace( entityId,
            createEntityRect( entityId++, {150, 50}, {{200, 170}}, sf::Color::Transparent, [this]() { _waitingForKey = true; _hotkeyPressed = HotkeysCodes::ARROW_TOP; }));
        _hotkeyEntityMap[HotkeysCodes::ARROW_TOP] = entityId - 1;
        _entitiesMenuOption.emplace(
            entityId, createEntityText(entityId++, HotkeysManager::get().keyToString(HotkeysManager::get().getKey(HotkeysCodes::ARROW_TOP)), {{200, 170}}, 20));
        _entitiesMenuOption.emplace( entityId,
            createEntityRect( entityId++, {150, 50}, {{300, 170}}, sf::Color::Transparent, [this]() { _waitingForKey = true; _hotkeyPressed = HotkeysCodes::ARROW_BOTTOM; }));
        _entitiesMenuOption.emplace(
            entityId, createEntityText(entityId++, HotkeysManager::get().keyToString(HotkeysManager::get().getKey(HotkeysCodes::ARROW_BOTTOM)), {{300, 170}}, 20));
        _hotkeyEntityMap[HotkeysCodes::ARROW_BOTTOM] = entityId - 1;
        _entitiesMenuOption.emplace( entityId,
            createEntityRect( entityId++, {150, 50}, {{400, 170}}, sf::Color::Transparent, [this]() { _waitingForKey = true; _hotkeyPressed = HotkeysCodes::ARROW_LEFT; }));
        _entitiesMenuOption.emplace(
            entityId, createEntityText(entityId++, HotkeysManager::get().keyToString(HotkeysManager::get().getKey(HotkeysCodes::ARROW_LEFT)), {{400, 170}}, 20));
        _hotkeyEntityMap[HotkeysCodes::ARROW_LEFT] = entityId - 1;
        _entitiesMenuOption.emplace( entityId,
            createEntityRect( entityId++, {150, 50}, {{500, 170}}, sf::Color::Transparent, [this]() { _waitingForKey = true; _hotkeyPressed = HotkeysCodes::ARROW_RIGHT; }));
        _entitiesMenuOption.emplace(
            entityId, createEntityText(entityId++, HotkeysManager::get().keyToString(HotkeysManager::get().getKey(HotkeysCodes::ARROW_RIGHT)), {{500, 170}}, 20));
        _hotkeyEntityMap[HotkeysCodes::ARROW_RIGHT] = entityId - 1;
        _entitiesMenuOption.emplace( entityId,
            createEntityRect( entityId++, {150, 50}, {{600, 170}}, sf::Color::Transparent, [this]() { _waitingForKey = true; _hotkeyPressed = HotkeysCodes::AUTO_FIRE; }));
        _entitiesMenuOption.emplace(
            entityId, createEntityText(entityId++, HotkeysManager::get().keyToString(HotkeysManager::get().getKey(HotkeysCodes::AUTO_FIRE)), {{600, 170}}, 20));
        _hotkeyEntityMap[HotkeysCodes::AUTO_FIRE] = entityId - 1;
        _entitiesMenuOption.emplace( entityId,
            createEntityRect( entityId++, {150, 50}, {{700, 170}}, sf::Color::Transparent, [this]() { _waitingForKey = true; _hotkeyPressed = HotkeysCodes::SHOOT; }));
        _entitiesMenuOption.emplace(
            entityId, createEntityText(entityId++, HotkeysManager::get().keyToString(HotkeysManager::get().getKey(HotkeysCodes::SHOOT)), {{700, 170}}, 20));
        _hotkeyEntityMap[HotkeysCodes::SHOOT] = entityId - 1;

// Adaptability
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, "Font for people with reading difficulties", {{40, 240}}, 20));
        _entitiesMenuOption.emplace( entityId,
            createEntityOptionButton(entityId++, {{720, 240}}, [this]() { setAdaptabilityText(); }));
    
// Size of elements
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, "Size of elements", {{40, 310}}, 20));
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, "Enlarge", {{545, 280}}, 15));
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, std::to_string(getElementSize()), {{520, 300}}, 15));
        _entitiesMenuOption.emplace( entityId,
            createEntitySlider( entityId++, {0, 100}, {{545, 310}}, [this]() { return getElementSize(); }, [this](int newValue) { setElementSize(newValue); }));
        
// Contrast
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, "High contrast", {{40, 380}}, 20));
        _entitiesMenuOption.emplace(
            entityId, createEntityOptionButton(entityId++, {{720, 380}}, [this]() { setContrast(); }));

// Difficulty
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, "High difficulty", {{40, 450}}, 20));
        _entitiesMenuOption.emplace(
            entityId, createEntityOptionButton(entityId++, {{720, 450}}, [this]() { setDifficulty(); }));

// Controller
        _entitiesMenuOption.emplace( entityId,
            createEntityText(entityId++, "Controller  mode", {{40, 520}}, 20));
        _entitiesMenuOption.emplace(
            entityId, createEntityOptionButton(entityId++, {{720, 520}}, [this]() { setControl(); }));
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