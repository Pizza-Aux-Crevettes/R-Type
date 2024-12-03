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

#include "../include/Client.hpp"
#include <thread>
#include "../../external/SFML/include/SFML/Graphics.hpp"
#include "../../external/SFML/include/SFML/Window.hpp"


Client::Client(){}

Client::~Client(){}

void Client::listenServer(){
    while (true){
        std::cout <<  "écoute le serveur et stocke les données qu'il envoie" << std::endl;
    }
}

void Client::manageClient(){

    std::thread serverThread(listenServer);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Client Game");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();    

        window.display();
    }
    serverThread.join();   
}


void Client::setItems(std::vector<std::any> items){
    _items = items;
}

std::vector<std::any> Client::getItems() {
    return _items;
}