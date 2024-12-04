/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** This file declares the `Client` class, responsible for managing the
** client's entities and items in the game context. It allows for the
** creation, updating, and drawing of items as well as setting their
** properties like position, text, and sprites.
** Client.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <any>
#include <iostream>
#include <functional>


class Client {
  private:
    std::vector<std::any> _items;

  public:
    Client();
    ~Client();
    void manageClient();
    void setItems(std::vector<std::any> items);
    std::vector<std::any> getItems();
    void listenServer(sf::RenderWindow* win);
};