/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** This file declares the `EntityManager` class, responsible for managing the
** entity list.
** EntityManager.hpp
*/

#include <any>
#include <components/Position.hpp>
#include <components/Shape.hpp>
#include <components/Sprite.hpp>
#include <components/Texture.hpp>
#include <iostream>
#include <map>
#include "Entity.hpp"
#include "System.hpp"

class EntityManager {

  private:
    std::map<int, GameEngine::Entity> _entities;
    EntityManager();
    ~EntityManager();
    std::map<int, std::map<std::string, std::any>> _items;
    std::map<int, std::map<std::string, std::any>> _updateItems;

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
    sf::Texture manageBackground(sf::RenderWindow& window);
};