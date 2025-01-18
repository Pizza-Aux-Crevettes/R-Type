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
#include <Entity.hpp>
#include <components/Position.hpp>
#include <components/Sprite.hpp>
#include <components/Texture.hpp>
#include <menu/OptionMenu.hpp>
#include <thread>
#include "EntityManager.hpp"
#include "component/hotkey/HotkeysManager.hpp"
#include "component/sound/SoundManager.hpp"
#include "menu/Menu.hpp"
#include "health/LifeBar.hpp"
#include "menu/LoseMenu.hpp"
#include "network/protocol/NetworkClient.hpp"
#include "network/protocol/Protocol.hpp"
#include "network/socket/TcpSocket.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"
#include "menu/WinMenu.hpp"

class NetworkClient;

class Client {
  private:
    std::map<int, std::map<std::string, std::any>> _items;
    std::map<int, std::map<std::string, std::any>> _updateItems;
    std::map<int, std::shared_ptr<GameEngine::Entity>> _entities;
    std::map<int, GameEngine::Entity> _displayEntities;
    bool _isPlay = false;
    std::string _username = "";
    std::string _port;
    std::string _ip;
    sf::Event _event;
    double _viewportX;
    bool _isWin;

  public:
    Client();
    ~Client();
    static Client& get();
    void manageClient();
    void manageBackground(GameEngine::System system, sf::Clock clock,
                          sf::Texture background);
                          void manageSound();
    void updateGameState(sf::RenderWindow& window, GameEngine::System& system, LifeBar& lifeBarMenu);
    void initializeServer(bool& serverInitialized, std::unique_ptr<NetworkClient>& networkClient, std::thread& serverThread, sf::RenderWindow& window);
    void handleAutoFire(sf::Clock& clock);
    void processEvents(sf::RenderWindow& window, GameEngine::System& system, OptionMenu& optionMenu, bool serverInitialized);

    void setIsPlayed();
    bool getIsPlayed();

    void setUsername(std::string username);
    std::string getUsername();

    void setPort(std::string port);
    std::string getPort();

    void setIp(std::string Ip);
    std::string getIp();

    void setViewport(double viewport);
    double getViewport();

    void setDisplayEntity(std::map<int, GameEngine::Entity> entities);
    sf::Event getEvent();

    void setIsWinGame();
    bool getIsWinGame();
};