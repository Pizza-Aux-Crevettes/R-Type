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

Menu& Menu::get() {
    static Menu instance;
    return instance;
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
    auto buttonRect = ButtonRect(size, color, false);
    buttonRect.setCallback(callback);
    rectEntity.addComponent(buttonRect);
    rectEntity.addComponent(Position(position));
    return rectEntity;
}

GameEngine::Entity Menu::createEntityText(
    int id, const std::string text,
    const std::vector<std::pair<float, float>> position,
    unsigned int fontSize) {
    auto newEntity = GameEngine::Entity(id);
    newEntity.addComponent(Text(text, OptionMenu::get().getAdaptabilityText(), fontSize));
    newEntity.addComponent(Position(position));
    newEntity.addComponent(Color({255, 255, 255, 255}));
    return newEntity;
}

GameEngine::Entity
Menu::createEntityInput(int id, int fontSize,
                        const std::vector<std::pair<float, float>> position,
                        std::string inputVar) {
    auto inputEntity = GameEngine::Entity(id);
    inputEntity.addComponent(Text(inputVar, OptionMenu::get().getAdaptabilityText(), fontSize));
    inputEntity.addComponent(Position(position));
    inputEntity.addComponent(Color({255, 255, 255, 255}));
    return inputEntity;
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

void Menu::initMainMenu(sf::RenderWindow& window, GameEngine::System system) {
    if (_currentMenuState == MenuState::MainMenu) {
        if (!_entitiesInitialized) {
            GetResponsiveValue responsive;
            int currentWidth = window.getSize().x;
            int currentHeight = window.getSize().y;

            int entityId = 0;

            float verticalSpacing = (1080 - 3) / (3 + 2);

            _entitiesMenu.emplace(
                entityId,
                createEntitySprite(
                    entityId++,
                    {responsive.getResponsiveSizeX(1920, currentWidth, 5),
                     responsive.getResponsiveSizeY(1080, currentHeight, 5)},
                    "assets/sprite/space.png", {0, 0, 400, 400},
                    {{responsive.getResponsivePosX(1920, currentWidth, -400),
                      responsive.getResponsivePosY(1080, currentHeight,
                                                   -170)}}));
            _entitiesMenu.emplace(
                entityId,
                createEntityRect(
                    entityId++, {145, 45},
                    {{responsive.getResponsivePosX(1920, currentWidth, 850),
                    responsive.getResponsivePosY(1080, currentHeight, 320)}},
                    sf::Color::Transparent, [this]() {Client::get().setIsPlayed(); }));

            _entitiesMenu.emplace(
                entityId,
                createEntityText(
                    entityId++, "PLAY",
                    {{responsive.getResponsivePosX(1920, currentWidth, 960),
                    responsive.getResponsivePosY(1080, currentHeight, 330)}},
                    50));
            _entitiesMenu.emplace(
                entityId,
                createEntityRect(
                    entityId++, {205, 45},
                    {{responsive.getResponsivePosX(1920, currentWidth, 810),
                    responsive.getResponsivePosY(1080, currentHeight, 450)}},
                    sf::Color::Transparent, [this]() {
                        _currentMenuState = MenuState::OptionMenu;
                        isClickedInput(false, false, false); }));

            _entitiesMenu.emplace(
                entityId,
                createEntityText(
                    entityId++, "OPTION",
                    {{responsive.getResponsivePosX(1920, currentWidth, 960),
                    responsive.getResponsivePosY(1080, currentHeight, 465)}},
                    50));
            _entitiesMenu.emplace(
                entityId,
                createEntityRect(
                    entityId++, {125, 45},
                    {{responsive.getResponsivePosX(1920, currentWidth, 865),
                    responsive.getResponsivePosY(1080, currentHeight, 590)}},
                    sf::Color::Transparent, [this, &window]() { window.close(); }));

            _entitiesMenu.emplace(
                entityId,
                createEntityText(
                    entityId++, "EXIT",
                    {{responsive.getResponsivePosX(1920, currentWidth, 960),
                    responsive.getResponsivePosY(1080, currentHeight, 600)}},
                    50));
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
                    {{responsive.getResponsivePosX(1920, currentWidth, 180),
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
                      responsive.getResponsivePosY(1080, currentHeight,
                                                   -65)}}));

            _entitiesMenu.emplace(
                entityId,
                createEntityRect(
                    entityId++,
                    {responsive.getResponsiveSizeX(1920, currentWidth, 300),
                     responsive.getResponsiveSizeY(1080, currentHeight, 50)},
                    {{responsive.getResponsivePosX(1920, currentWidth, 500),
                      responsive.getResponsivePosY(1080, currentHeight, 870)}},
                    sf::Color(169, 169, 169), [this]() {
                        isClickedInput(false, false, true);
                    }));
            _entitiesMenu.emplace(
                entityId,
                createEntityInput(
                    entityId++, 30,
                    {{responsive.getResponsivePosX(1920, currentWidth, 640),
                      responsive.getResponsivePosY(1080, currentHeight, 800)}},
                    "Username:"));
            _entitiesMenu.emplace(
                entityId,
                createEntityInput(
                    entityId++, 20,
                    {{responsive.getResponsivePosX(1920, currentWidth, 510),
                      responsive.getResponsivePosY(1080, currentHeight, 875)}},
                    ""));
            _usernameId = entityId;
            _entitiesMenu.emplace(
                entityId,
                createEntityRect(
                    entityId++,
                    {responsive.getResponsiveSizeX(1920, currentWidth, 300),
                     responsive.getResponsiveSizeY(1080, currentHeight, 50)},
                    {{responsive.getResponsivePosX(1920, currentWidth, 1150),
                      responsive.getResponsivePosY(1080, currentHeight, 870)}},
                    sf::Color(169, 169, 169), [this]() {
                        isClickedInput(true, false, false);
                    }));
            _entitiesMenu.emplace(
                entityId,
                createEntityInput(
                    entityId++, 30,
                    {{responsive.getResponsivePosX(1920, currentWidth, 1300),
                      responsive.getResponsivePosY(1080, currentHeight, 800)}},
                    "Adresse IP:"));
            _entitiesMenu.emplace(
                entityId,
                createEntityInput(
                    entityId++, 20,
                    {{responsive.getResponsivePosX(1920, currentWidth, 1160),
                      responsive.getResponsivePosY(1080, currentHeight, 875)}},
                    ""));
            _ipId = entityId;
            _entitiesInitialized = true;
        } else {
            _entitiesMenu.at(_usernameId)
                .getComponent<Text>()
                .setString(Client::get().getUsername());
            _entitiesMenu.at(_ipId).getComponent<Text>().setString(
                Client::get().getIp());
        }
        system.render(window, _entitiesMenu);
    }
}

void Menu::displayMenu(sf::RenderWindow& window, GameEngine::System system) {
    std::map<int, GameEngine::Entity> entities;

    switch (_currentMenuState) {
    case MenuState::MainMenu:
        initMainMenu(window, system);
        break;
    case MenuState::OptionMenu: {
        OptionMenu::get().displayOptionMenu(window, system, _entitiesMenu);
        break;
    };
    }
}

void Menu::setMenuState(MenuState state) {
    _currentMenuState = state;
}