/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Menu
*/

#include "menu/Menu.hpp"
#include "Client.hpp"
#include "network/protocol/Protocol.hpp"
#include "network/socket/TcpSocket.hpp"

Menu::Menu() {}

Menu::~Menu() {}

GameEngine::Entity
Menu::createEntityButton(int id, std::string title, std::string font,
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

GameEngine::Entity
Menu::createEntitySprite(int id, const std::pair<float, float> size,
                         std::string texture, std::vector<int> textureRect,
                         const std::vector<std::pair<float, float>> position) {
    auto newEntity = GameEngine::Entity(id);
    newEntity.addComponent(Sprite(size));
    newEntity.addComponent(Texture(texture, textureRect));
    newEntity.addComponent(Position(position));
    return newEntity;
}

void Menu::isClickedPlay() {
    std::cout << "Button play clicked!" << std::endl;
    SmartBuffer smartBuffer;

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::NEW_PLAYER);
    smartBuffer << std::string{"Benjamin"};
    TcpSocket::send(smartBuffer);

    Client::get().setIsPlayed();
}

void Menu::isClickedExit() {
    std::cout << "Button Exit clicked!" << std::endl;
}

void Menu::initMainMenu(sf::RenderWindow& window, GameEngine::System system) {
    if (_currentMenuState == MenuState::MainMenu) {
        if (!_entitiesInitialized) {
            int entityId = 0;

            float totalButtonHeight = 3;
            float verticalSpacing = (1080 - totalButtonHeight) / (3 + 2);

            _entitiesMenu.emplace(
                entityId,
                createEntitySprite(entityId++, {8, 8}, "assets/sprite/map.png",
                                   {0, 0, 200, 200}, {{-1300, -300}}));
            _entitiesMenu.emplace(
                entityId, createEntityButton(
                              entityId++, "PLAY", "assets/font/Inter_Bold.ttf",
                              50, {{1920 / 2 - 60, (verticalSpacing + 130)}},
                              [this]() { isClickedPlay(); }));
            _entitiesMenu.emplace(
                entityId,
                createEntityButton(
                    entityId++, "OPTION", "assets/font/Inter_Bold.ttf", 50,
                    {{1920 / 2 - 100, verticalSpacing * 2 + 50}},
                    [this]() { _currentMenuState = MenuState::OptionMenu; }));
            _entitiesMenu.emplace(
                entityId, createEntityButton(
                              entityId++, "EXIT", "assets/font/Inter_Bold.ttf",
                              50, {{1920 / 2 - 50, verticalSpacing * 3 - 20}},
                              [this]() { isClickedExit(); }));
            _entitiesMenu.emplace(
                entityId, createEntitySprite(entityId++, {6, 6},
                                             "assets/sprite/spaceship.png",
                                             {0, 18, 34, 15}, {{30, 100}}));
            _entitiesMenu.emplace(
                entityId, createEntitySprite(entityId++, {5, 5},
                                             "assets/sprite/shoot_blue.png",
                                             {165, 0, 65, 15}, {{350, 100}}));
            _entitiesMenu.emplace(
                entityId, createEntitySprite(entityId++, {5, 5},
                                             "assets/sprite/enemy.png",
                                             {0, 0, 50, 80}, {{280, 820}}));
            _entitiesMenu.emplace(
                entityId, createEntitySprite(entityId++, {5, 5},
                                             "assets/sprite/canon.png",
                                             {165, 0, 33, 30}, {{1600, -50}}));
            _entitiesMenu.emplace(
                entityId, createEntitySprite(entityId++, {5, 5},
                                             "assets/sprite/canon.png",
                                             {33, 33, 33, 30}, {{1600, 970}}));
            _entitiesMenu.emplace(
                entityId, createEntitySprite(entityId++, {5, 5},
                                             "assets/sprite/intact-boss.png",
                                             {0, 0, 200, 200}, {{1400, 200}}));
        }
        system.render(window, _entitiesMenu);
    }
}

void Menu::displayMenu(sf::RenderWindow& window, GameEngine::System system,
                       OptionMenu& optionMenu) {
    std::map<int, GameEngine::Entity> entities;
    sf::SoundBuffer ambienBuffer;
    sf::SoundBuffer clickBuffer;

    if (!ambienBuffer.loadFromFile("assets/sounds/ambien-song.wav")) {
        std::cerr << "Error: unable to load the audio file." << std::endl;
    }

    if (!clickBuffer.loadFromFile("assets/sounds/click-menu.wav")) {
        std::cerr << "Error: unable to load the audio file." << std::endl;
    }

    sf::Sound ambienSound;
    sf::Sound clickMenuSound;

    ambienSound.setBuffer(ambienBuffer);
    clickMenuSound.setBuffer(clickBuffer);

    ambienSound.play();

    switch (_currentMenuState) {
    case MenuState::MainMenu:
        initMainMenu(window, system);
        break;
    case MenuState::OptionMenu: {
        optionMenu.displayOptionMenu(window, system);
        break;
    };
    }
}
