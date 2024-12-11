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
#include <functional>
#include <iostream>

class Client {
  private:
    std::map<int, std::map<std::string, std::any>> _items;
    std::map<int, std::map<std::string, std::any>> _updateItems;
    std::map<int, std::any> _entities;

  public:
    Client();
    ~Client();
    void manageClient();
    void setItems(std::map<int, std::map<std::string, std::any>>);
    std::map<int, std::map<std::string, std::any>> getItems();

    void setUpdateItems(std::map<int, std::map<std::string, std::any>>);
    std::map<int, std::map<std::string, std::any>> getUpdateItems();
  
    void setEntities(std::map<int, std::any>);
    std::map<int, std::any> getEntities();

    void listenServer(sf::RenderWindow* win);
    void CompareEntities();
    void CompareComponents (std::map<std::string, std::any> entity, std::map<std::string, std::any> updateEntity);

};