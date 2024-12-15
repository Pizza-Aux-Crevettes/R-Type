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
#include "InputClient.hpp"
#include <Entity.hpp>
#include <System.hpp>
#include <components/Position.hpp>
#include <components/Sprite.hpp>
#include <components/Texture.hpp>
#include <thread>

Client::Client() {}

Client::~Client() {}

void Client::listenServer(sf::RenderWindow* win) {
    std::map<int, std::map<std::string, std::any>> newItems = {
        {1,
         {{"Texture", std::string("../assets/sprite/tentacles.png")},
          {"Position", std::pair<float, float>(500.0f, 500.0f)}}},
        {2,
         {{"Texture", std::string("../assets/sprite/spaceship.png")},
          {"Position", std::pair<float, float>(200.0, 200.0)}}}};
    // Le premier truc que nous envoie Benjamin au départ

    setItems(newItems);
    CompareEntities();

    while (win->isOpen()) {
        std::map<int, std::map<std::string, std::any>> updateItems = {
            {1,
             {{"Texture", std::string("../assets/sprite/tentacles.png")},
              {"Position", std::pair<float, float>(100.0f, 100.0f)}}},
            {2,
             {{"Texture", std::string("../assets/sprite/tentacles.png")},
              {"Position", std::pair<float, float>(
                               100.0, 100.0)}}}}; // exemple des trucs suivant
                                                  // que nous envoie Benjamin
        setUpdateItems(updateItems);
        CompareEntities();
    }
}

void Client::CompareEntities() {
    for (const auto& [id, entity] : _items) {
        if (auto search = _updateItems.find(id); search != _updateItems.end()) {
            CompareComponents(entity, search->second, id);
        } else {
            CreateEntity(entity, id);
        }
    }
    if (_updateItems.size() > 0) {
        setItems(_updateItems);
    }
}

void Client::CreateEntity(std::map<std::string, std::any> entity, int id) {
    auto player = std::make_unique<GameEngine::Entity>(id);
    for (const auto& [key, component] : entity) {
        if (key == "Texture") {
            player->addComponent(Sprite());
            player->addComponent(
                Texture(std::any_cast<std::string>(component)));
        }
        if (key == "Position") {
            player->addComponent(
                Position(std::any_cast<std::pair<float, float>>(component)));
        }
    }
    _entities.insert_or_assign(id, std::move(player));
}

void Client::CompareComponents(std::map<std::string, std::any> entity,
                               std::map<std::string, std::any> updateEntity,
                               int id) {
    GameEngine::System system;
    for (const auto& [key, component] : updateEntity) {
        if (auto search = entity.find(key); search != entity.end()) {
            if (component.type() == search->second.type()) {
                if (component.type() == typeid(std::pair<float, float>)) {
                    if (std::any_cast<std::pair<float, float>>(component) !=
                        std::any_cast<std::pair<float, float>>(
                            search->second)) {

                        std::cout << "tout est à jour" << std::endl;
                        system.update(*_entities[id],
                                      GameEngine::UpdateType::Position,
                                      component);
                    }
                } else if (component.type() == typeid(float)) {
                    if (std::any_cast<float>(component) !=
                        std::any_cast<float>(search->second)) {
                        std::cout << "tout est à jour" << std::endl;
                    }
                } else if (component.type() == typeid(std::string)) {
                    if (std::any_cast<std::string>(component) !=
                        std::any_cast<std::string>(search->second)) {
                        std::cout << std::any_cast<std::string>(component)
                                  << " "
                                  << std::any_cast<std::string>(search->second)
                                  << std::endl;
                        std::cout << "tout est à jour" << std::endl;
                    }
                }
            }
        } else {
            std::cout << "le composant donné n'existe pas dans l'entité"
                      << std::endl;
        }
    }
}

void Client::manageClient() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Client Game");
    std::thread serverThread(std::bind(&Client::listenServer, this, &window));
    InputClient input;
    GameEngine::System system;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                input.checkKey(event);
        }
        window.clear();
        if (_entities.size() > 0) {
            system.render(window, _entities);
        }
        window.display();
    }
    serverThread.join();
}

void Client::setItems(std::map<int, std::map<std::string, std::any>> items) {
    _items = items;
}

std::map<int, std::map<std::string, std::any>> Client::getItems() {
    return _items;
}

void Client::setUpdateItems(
    std::map<int, std::map<std::string, std::any>> updateItems) {
    _updateItems = updateItems;
}

std::map<int, std::map<std::string, std::any>> Client::getUpdateItems() {
    return _updateItems;
}

std::map<int, std::unique_ptr<GameEngine::Entity>>& Client::getEntities() {
    return _entities;
}