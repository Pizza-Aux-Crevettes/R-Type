/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** This file declares the `EntityManager` class, responsible for managing the
** entity list.
** EntityManager.hpp
*/

#pragma once

#include <any>
#include <components/Position.hpp>
#include <components/Shape.hpp>
#include <components/Sprite.hpp>
#include <components/Texture.hpp>
#include <components/Text.hpp>
#include <components/Link.hpp>
#include <iostream>
#include <map>
#include <random>
#include "Entity.hpp"
#include "System.hpp"
#include "Client.hpp"

class EntityManager {

  private:
    std::map<int, GameEngine::Entity> _entities;
    EntityManager();
    ~EntityManager();
    std::map<int, std::map<std::string, std::any>> _items;
    std::map<int, std::map<std::string, std::any>> _updateItems;
    std::vector<int> _playerSpriteColor;
    std::mutex _mutex;
    int _bossId;

  public:
    static EntityManager& get();

    void setEntityList(std::map<int, GameEngine::Entity> entities);
    std::map<int, GameEngine::Entity>& getEntityList();

    void CompareEntities(int, std::map<std::string, std::any>,
                         std::pair<float, float> updatePosition);
    void CreateEntity(int, std::map<std::string, std::any>);

    void setItems(std::map<int, std::map<std::string, std::any>>);
    std::map<int, std::map<std::string, std::any>> getItems();
    void addItem(std::map<int, std::map<std::string, std::any>> items);

    void setUpdateItems(std::map<int, std::map<std::string, std::any>>);
    std::map<int, std::map<std::string, std::any>> getUpdateItems();

    std::vector<int> getPlayerColor();
    void setPlayerColor(int playerId);

    void setBossId(int id);
    
    std::mutex& getMutex();
    sf::Texture manageBackground(sf::RenderWindow& window);
    std::vector<int> setEnemy(int num);

    void winGame(int id, int health);
};