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
#include <System.hpp>
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
    Menu menu;

    while (window.isOpen()) {
        std::map<int, GameEngine::Entity> entitiesList =
            EntityManager::get().getEntityList();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                input.checkKey(event);
        }
        window.clear();
        if (!Client::get().getIsPlayed()) {
            menu.displayMenu(window, system);
        } else {
            if (entitiesList.size() > 0) {
                system.render(window, entitiesList);
            }
        }
        window.display();
    }
}
