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

#include <Entity.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <System.hpp>
#include <any>
#include <functional>
#include <iostream>
#include <memory>
#include "components/Sound.hpp"

class Client {
  private:
    std::map<int, std::map<std::string, std::any>> _items;
    std::map<int, std::map<std::string, std::any>> _updateItems;
    std::map<int, std::shared_ptr<GameEngine::Entity>> _entities;
    bool _isPlay = false;
    std::string _username = "";
    std::string _port;
    std::string _ip;
    sf::Event _event;
    int32_t _viewportX;
    Sound _bulletSound;

  public:
    Client();
    ~Client();
    static Client& get();
    void manageClient();
    void manageBackground(GameEngine::System system, sf::Clock clock,
                          sf::Texture background);
    void setIsPlayed();
    bool getIsPlayed();
    void setUsername(std::string username);
    void setPort(std::string port);
    void setIp(std::string Ip);
    void setViewport(int32_t viewport);
    int32_t getViewport();
    std::string getUsername();
    std::string getPort();
    std::string getIp();
    sf::Event getEvent();
    Sound getBulletSound();
    void setBulletSound(Sound);
};