/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Menu
*/

#include "menu/Menu.hpp"
#include <SmartBuffer.hpp>
#include "Client.hpp"
#include "network/protocol/Protocol.hpp"
#include "network/socket/TcpSocket.hpp"
#include "util/getResponsiveValue.hpp"

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

GameEngine::Entity
Menu::createEntityRect(int id, const std::pair<int, int> size,
                       const std::vector<std::pair<float, float>> position,
                       sf::Color color, std::function<void()> callback) {
    auto rectEntity = GameEngine::Entity(id);
    auto buttonRect = ButtonRect(size, color);
    buttonRect.setCallback(callback);
    rectEntity.addComponent(buttonRect);
    rectEntity.addComponent(Position(position));
    return rectEntity;
}

GameEngine::Entity
Menu::createEntityInput(int id, std::string font, int fontSize,
                        const std::vector<std::pair<float, float>> position,
                        std::string inputVar) {
    auto inputEntity = GameEngine::Entity(id);
    inputEntity.addComponent(Text(inputVar, font, fontSize));
    inputEntity.addComponent(Position(position));
    inputEntity.addComponent(Color({255, 255, 255, 255}));
    return inputEntity;
}

void Menu::isClickedPlay() {
    std::cout << "Button play clicked!" << std::endl;
    Client::get().setIsPlayed();
}

void Menu::isClickedInput(bool isIpClicked, bool isPortClicked,
                          bool isUsernameClicked) {

    _isIpClicked = isIpClicked;
    _isPortClicked = isPortClicked;
    _isUsernameClicked = isUsernameClicked;
}

void Menu::setupInput(const sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (_isIpClicked) {
            std::string ip = Client::get().getIp();
            if (event.text.unicode == '\b') {
                if (!ip.empty()) {
                    ip.pop_back();
                }
                Client::get().setIp(ip);
            } else if (event.text.unicode < 128 && ip.size() < 15) {
                ip += static_cast<char>(event.text.unicode);
            }
            Client::get().setIp(ip);
        } else if (_isPortClicked) {
            std::string port = Client::get().getPort();
            if (event.text.unicode == '\b') {
                if (!port.empty()) {
                    port.pop_back();
                }
                Client::get().setPort(port);
            } else if (event.text.unicode < 128 && port.size() < 15) {
                port += static_cast<char>(event.text.unicode);
            }
            Client::get().setPort(port);
        } else if (_isUsernameClicked) {
            std::string username = Client::get().getUsername();
            if (event.text.unicode == '\b') {
                if (!username.empty()) {
                    username.pop_back();
                }
                Client::get().setUsername(username);
            } else if (event.text.unicode < 128 && username.size() < 15) {
                username += static_cast<char>(event.text.unicode);
            }
            Client::get().setUsername(username);
        }
    }
}

void Menu::isClickedExit() {
    std::cout << "Button Exit clicked!" << std::endl;
}

void Menu::initMainMenu(sf::RenderWindow& window, GameEngine::System system) {
    if (_currentMenuState == MenuState::MainMenu) {
        if (!_entitiesInitialized) {
            GetResponsiveValue responsive;
            int currentWidth = window.getSize().x;
            int currentHeight = window.getSize().y;
            std::cout << currentWidth << std::endl;

            int entityId = 0;

            float verticalSpacing = (1080 - 3) / (3 + 2);

            _entitiesMenu.emplace(
                entityId,
                createEntitySprite(
                    entityId++,
                    {responsive.getResponsiveSizeX(1920, currentWidth, 8),
                     responsive.getResponsiveSizeY(1080, currentHeight, 8)},
                    "assets/sprite/map.png", {0, 0, 200, 200},
                    {{responsive.getResponsivePosX(1920, currentWidth, -1300),
                      responsive.getResponsivePosY(1080, currentHeight,
                                                   -300)}}));
            _entitiesMenu.emplace(
                entityId,
                createEntityButton(
                    entityId++, "PLAY", "assets/font/Inter_Bold.ttf", 50,
                    {{responsive.getResponsivePosX(1920, currentWidth, 900),
                      responsive.getResponsivePosY(1080, currentHeight, 345)}},
                    [this]() { isClickedPlay(); }));
            _entitiesMenu.emplace(
                entityId,
                createEntityButton(
                    entityId++, "OPTION", "assets/font/Inter_Bold.ttf", 50,
                    {{responsive.getResponsivePosX(1920, currentWidth, 860),
                      responsive.getResponsivePosY(1080, currentHeight, 480)}},
                    [this]() { _currentMenuState = MenuState::OptionMenu; }));
            _entitiesMenu.emplace(
                entityId,
                createEntityButton(
                    entityId++, "EXIT", "assets/font/Inter_Bold.ttf", 50,
                    {{responsive.getResponsivePosX(1920, currentWidth, 910),
                      responsive.getResponsivePosY(1080, currentHeight, 626)}},
                    [this]() { isClickedExit(); }));
            _entitiesMenu.emplace(
                entityId,
                createEntitySprite(
                    entityId++,
                    {responsive.getResponsiveSizeX(1920, currentWidth, 6),
                     responsive.getResponsiveSizeY(1080, currentHeight, 6)},
                    "assets/sprite/spaceship.png", {0, 18, 34, 15},
                    {{responsive.getResponsivePosX(1920, currentWidth, 30),
                      responsive.getResponsivePosY(1080, currentHeight,
                                                   100)}}));
            _entitiesMenu.emplace(
                entityId,
                createEntitySprite(
                    entityId++,
                    {responsive.getResponsiveSizeX(1920, currentWidth, 5),
                     responsive.getResponsiveSizeY(1080, currentHeight, 5)},
                    "assets/sprite/shoot_blue.png", {165, 0, 65, 15},
                    {{responsive.getResponsivePosX(1920, currentWidth, 350),
                      responsive.getResponsivePosY(1080, currentHeight,
                                                   100)}}));
            _entitiesMenu.emplace(
                entityId,
                createEntitySprite(
                    entityId++,
                    {responsive.getResponsiveSizeX(1920, currentWidth, 5),
                     responsive.getResponsiveSizeY(1080, currentHeight, 5)},
                    "assets/sprite/enemy.png", {0, 0, 50, 80},
                    {{responsive.getResponsivePosX(1920, currentWidth, 280),
                      responsive.getResponsivePosY(1080, currentHeight,
                                                   820)}}));
            _entitiesMenu.emplace(
                entityId,
                createEntitySprite(
                    entityId++,
                    {responsive.getResponsiveSizeX(1920, currentWidth, 5),
                     responsive.getResponsiveSizeY(1080, currentHeight, 5)},
                    "assets/sprite/canon.png", {165, 0, 33, 30},
                    {{responsive.getResponsivePosX(1920, currentWidth, 1600),
                      responsive.getResponsivePosY(1080, currentHeight,
                                                   -50)}}));
            _entitiesMenu.emplace(
                entityId,
                createEntitySprite(
                    entityId++,
                    {responsive.getResponsiveSizeX(1920, currentWidth, 5),
                     responsive.getResponsiveSizeY(1080, currentHeight, 5)},
                    "assets/sprite/canon.png", {33, 33, 33, 30},
                    {{responsive.getResponsivePosX(1920, currentWidth, 1600),
                      responsive.getResponsivePosY(1080, currentHeight,
                                                   970)}}));
            _entitiesMenu.emplace(
                entityId,
                createEntitySprite(
                    entityId++,
                    {responsive.getResponsiveSizeX(1920, currentWidth, 5),
                     responsive.getResponsiveSizeY(1080, currentHeight, 5)},
                    "assets/sprite/intact-boss.png", {0, 0, 200, 200},
                    {{responsive.getResponsivePosX(1920, currentWidth, 1400),
                      responsive.getResponsivePosY(1080, currentHeight, 1)}}));

            _entitiesMenu.emplace(
                entityId,
                createEntityRect(
                    entityId++,
                    {responsive.getResponsiveSizeX(1920, currentWidth, 150),
                     responsive.getResponsiveSizeY(1080, currentHeight, 50)},
                    {{responsive.getResponsivePosX(1920, currentWidth, 1300),
                      responsive.getResponsivePosY(1080, currentHeight, 80)}},
                    sf::Color::Red, [this]() {
                        isClickedInput(false, false, true);
                    })); // username inputRect
            _entitiesMenu.emplace(
                entityId,
                createEntityInput(
                    entityId++, "assets/font/Inter_Bold.ttf", 40,
                    {{responsive.getResponsivePosX(1920, currentWidth, 1050),
                      responsive.getResponsivePosY(1080, currentHeight, 78)}},
                    "Username"));
            _entitiesMenu.emplace(
                entityId,
                createEntityInput(
                    entityId++, "assets/font/Inter_Bold.ttf", 40,
                    {{responsive.getResponsivePosX(1920, currentWidth, 1305),
                      responsive.getResponsivePosY(1080, currentHeight, 78)}},
                    "")); // username input text
            _usernameId = entityId;
            _entitiesMenu.emplace(
                entityId,
                createEntityRect(
                    entityId++,
                    {responsive.getResponsiveSizeX(1920, currentWidth, 150),
                     responsive.getResponsiveSizeY(1080, currentHeight, 50)},
                    {{responsive.getResponsivePosX(1920, currentWidth, 1300),
                      responsive.getResponsivePosY(1080, currentHeight, 150)}},
                    sf::Color::Red, [this]() {
                        isClickedInput(true, false, false);
                    })); // ip inputRect
            _entitiesMenu.emplace(
                entityId,
                createEntityInput(
                    entityId++, "assets/font/Inter_Bold.ttf", 40,
                    {{responsive.getResponsivePosX(1920, currentWidth, 1050),
                      responsive.getResponsivePosY(1080, currentHeight, 148)}},
                    "IP"));
            _entitiesMenu.emplace(
                entityId,
                createEntityInput(
                    entityId++, "assets/font/Inter_Bold.ttf", 40,
                    {{responsive.getResponsivePosX(1920, currentWidth, 1305),
                      responsive.getResponsivePosY(1080, currentHeight, 148)}},
                    "")); // ip input text
            _ipId = entityId;
            _entitiesMenu.emplace(
                entityId,
                createEntityRect(
                    entityId++,
                    {responsive.getResponsiveSizeX(1920, currentWidth, 150),
                     responsive.getResponsiveSizeY(1080, currentHeight, 50)},
                    {{responsive.getResponsivePosX(1920, currentWidth, 1300),
                      responsive.getResponsivePosY(1080, currentHeight, 220)}},
                    sf::Color::Red, [this]() {
                        isClickedInput(false, true, false);
                    })); // port inputRect
            _entitiesMenu.emplace(
                entityId,
                createEntityInput(
                    entityId++, "assets/font/Inter_Bold.ttf", 40,
                    {{responsive.getResponsivePosX(1920, currentWidth, 1050),
                      responsive.getResponsivePosY(1080, currentHeight, 218)}},
                    "Port"));
            _entitiesMenu.emplace(
                entityId,
                createEntityInput(
                    entityId++, "assets/font/Inter_Bold.ttf", 40,
                    {{responsive.getResponsivePosX(1920, currentWidth, 1305),
                      responsive.getResponsivePosY(1080, currentHeight, 218)}},
                    "")); // port input tex
            _portId = entityId;
            _entitiesInitialized = true;
        } else {
            _entitiesMenu.at(_usernameId)
                .getComponent<Text>()
                .setString(Client::get().getUsername());
            _entitiesMenu.at(_ipId).getComponent<Text>().setString(
                Client::get().getIp());
            _entitiesMenu.at(_portId).getComponent<Text>().setString(
                Client::get().getPort());
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
