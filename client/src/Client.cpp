/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** This file declares the `Client` class, responsible for managing the
** client's entities and items in the game context. It allows for the
** creation, updating, and drawing of items as well as setting their
** properties like position, text, and sprites.
** Client.cpp
*/

#include "Client.hpp"
#include <Entity.hpp>
#include <components/Position.hpp>
#include <components/Sprite.hpp>
#include <components/Texture.hpp>
#include <menu/OptionMenu.hpp>
#include <thread>
#include "EntityManager.hpp"
#include "component/hotkey/HotkeysManager.hpp"
#include "menu/Menu.hpp"

Client::Client() {}

Client::~Client() {}

void Client::manageBackground(GameEngine::System system, sf::Clock clock,
                              sf::Texture background) {

    sf::Vector2f textureOffset(0.f, 0.f);
    const float scrollSpeed = 100.f;
    std::map<int, GameEngine::Entity> entityList =
        EntityManager::get().getEntityList();

    sf::Time elapsed = clock.restart();
    textureOffset.x += scrollSpeed * elapsed.asSeconds();
    if (textureOffset.x > background.getSize().x) {
        textureOffset.x -= background.getSize().x;
    }
    sf::RectangleShape& shape =
        entityList.at(0).getComponent<Shape>().getRect();
    shape.setTextureRect(
        sf::IntRect(textureOffset.x, textureOffset.y, 800, 600));
}
Client& Client::get() {
    static Client instance;
    return instance;
}

void Client::setIsPlayed() {
    _isPlay = !_isPlay;
}

bool Client::getIsPlayed() {
    return _isPlay;
}

void Client::manageClient() {

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RTYPE");
    HotkeysManager input;
    GameEngine::System system;
    sf::Texture background = EntityManager::get().manageBackground();
    Menu menu;
    OptionMenu optionMenu;

    sf::Clock clock;
    while (window.isOpen()) {
        manageBackground(system, clock, background);
        std::map<int, GameEngine::Entity> entitiesList =
            EntityManager::get().getEntityList();
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::KeyPressed)
                input.checkKey(event);
            menu.setupInput(event);

        }
        window.clear();
        if (!Client::get().getIsPlayed()) {
            menu.displayMenu(window, system, optionMenu);
        } else {
            if (entitiesList.size() > 0) {
                system.render(window, entitiesList);
            }
        }
        window.display();
    }
}

void Client::setUsername(std::string username) {
    _username = username;
}
void Client::setPort(std::string port) {
    _port = port;
}
void Client::setIp(std::string Ip) {
    _ip = Ip;
}
std::string Client::getUsername() {
    return _username;
}
std::string Client::getPort() {
    return _port;
}
std::string Client::getIp() {
    return _ip;
}

sf::Event Client::getEvent() {
    return _event;
}
