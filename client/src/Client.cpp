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
    while (win->isOpen()) {
        // std::cout << "écoute le serveur et stocke les données qu'il envoie"
        //           << std::endl;
    }
}

void Client::manageClient() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Client Game");
    std::thread serverThread(std::bind(&Client::listenServer, this, &window));
    InputClient input_test;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                input_test.checkKey(event);
        }

        window.clear();

        window.display();
    }
    serverThread.join();
}

void Client::setItems(std::vector<std::any> items) {
    _items = items;
}

std::vector<std::any> Client::getItems() {
    return _items;
}