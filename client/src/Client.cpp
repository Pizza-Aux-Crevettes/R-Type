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
#include <thread>

Client::Client() {}

Client::~Client() {}

void Client::listenServer(sf::RenderWindow* win) {
    std::map<int, std::map<std::string, std::any>> newItems = {
        {1, {{"PosX", 500}, {"PosY", 500}, {"color", std::string("Rose")}, {"SizeX", 20}, {"SizeY", 30}}},
        {2, {{"PosX", 400}, {"PosY", 400}, {"color",std::string("Orange")}, {"SizeX", 40}, {"SizeY", 50}}},
    }; //Le premier truc que nous envoie Benjamin au départ

    setItems(newItems);

    while (win->isOpen()) {
        std::map<int, std::map<std::string, std::any>> updateItems = {
            {1, {{"PosX", 500}, {"PosY", 500}, {"color", std::string("Red")}, {"SizeX", 20}, {"SizeY", 30}}},
            {2, {{"PosX", 400}, {"PosY", 400}, {"color", std::string("Green")}, {"SizeX", 40}, {"SizeY", 50}}},
            {3, {{"PosX", 400}, {"PosY", 400}, {"color", std::string("Yellow")}, {"SizeX", 40}, {"SizeY", 50}}},
        }; // exemple des trucs suivant que nous envoie Benjamin
        setUpdateItems(updateItems);
        CompareEntities();
    }
}

void Client::CompareEntities () {

    for (const auto& [id, entity] : _updateItems) { //chercher dans la liste actuelle si l'id de l'update existe ou non
        if (auto search = _items.find(id); search != _items.end()) {
            std::cout << "l'entité existe déjà" << std::endl;
            CompareComponents(entity, search->second);
        } else {
            std::cout << "créer l'entité" << std::endl;
        }
    }
    setItems(_updateItems);
}

void Client::CompareComponents (std::map<std::string, std::any> entity, std::map<std::string, std::any> updateEntity) {
    for (const auto& [key, component] : updateEntity) {
        if (auto search = entity.find(key); search != entity.end()) {
            if (component.type() == search->second.type()) {
                if (component.type() == typeid(int)) {
                    if (std::any_cast<int>(component) == std::any_cast<int>(search->second)) {
                        std::cout << "tout est à jour" << std::endl;
                    }else {
                        std::cout << "il faut appeller system pour update" << std::endl;
                    }
                } else if (component.type() == typeid(float)) {
                    if (std::any_cast<float>(component) == std::any_cast<float>(search->second)) {
                        std::cout << "tout est à jour" << std::endl;
                    }else {
                        std::cout << "il faut appeller system pour update" << std::endl;
                    }
                } else if (component.type() == typeid(std::string)) {
                    if (std::any_cast<std::string>(component) == std::any_cast<std::string>(search->second)) {
                        std::cout << std::any_cast<std::string>(component) << " " << std::any_cast<std::string>(search->second) << std::endl;
                        std::cout << "tout est à jour" << std::endl;
                    }else {
                        std::cout << "il faut appeller system pour update" << std::endl;
                    }
                }
            }
        } else {
            std::cout << "le composant donné n'existe pas dans l'entité" << std::endl;
        }
    }
}

void Client::manageClient() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Client Game");
    std::thread serverThread(std::bind(&Client::listenServer, this, &window));
    InputClient input;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                input.checkKey(event);
        }
        window.clear();

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

void Client::setUpdateItems(std::map<int, std::map<std::string, std::any>> updateItems){
    _updateItems = updateItems;
}

std::map<int, std::map<std::string, std::any>> Client::getUpdateItems() {
    return _updateItems;
}
  
void Client::setEntities(std::map<int, std::any> entities) {
    _entities = entities;
}

std::map<int, std::any> Client::getEntities() {
    return _entities;
}