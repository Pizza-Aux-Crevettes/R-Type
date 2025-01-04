/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** This file declares the `EntityManager` class, responsible for managing the
** entity list.
** EntityManager.cpp
*/

#include "EntityManager.hpp"

EntityManager::EntityManager() {}

EntityManager::~EntityManager() {}

EntityManager& EntityManager::get() {
    static EntityManager instance;
    return instance;
}

void EntityManager::setEntityList(int id, GameEngine::Entity entity) {
    _entities.emplace(id, std::move(entity));
}

std::map<int, GameEngine::Entity> EntityManager::getEntityList() {
    return _entities;
}

void EntityManager::CompareEntities(int id,
                                    std::map<std::string, std::any> components,
                                    std::pair<float, float> updatePosition) {
    GameEngine::System system;
    if (auto search = _entities.find(id); search != _entities.end()) {
        system.update(id, _entities, GameEngine::UpdateType::Position,
                      updatePosition);
    } else {
        CreateEntity(id, components);
    }
}

void EntityManager::CreateEntity(int id,
                                 std::map<std::string, std::any> components) {
    auto newEntity = GameEngine::Entity(id);
    for (const auto& [key, component] : components) {
        if (key == "Texture") {
            newEntity.addComponent(Sprite());
            newEntity.addComponent(
                Texture(std::any_cast<std::string>(component)));
        }
        if (key == "Position") {
            newEntity.addComponent(
                Position({std::any_cast<std::pair<float, float>>(component)}));
        }
    }
    _entities.emplace(id, std::move(newEntity));
}

void EntityManager::setItems(
    std::map<int, std::map<std::string, std::any>> items) {
    _items = items;
}

void EntityManager::addItem(
    std::map<int, std::map<std::string, std::any>> items) {
    _items.insert(items.begin(), items.end());
}

std::map<int, std::map<std::string, std::any>> EntityManager::getItems() {
    return _items;
}

void EntityManager::setUpdateItems(
    std::map<int, std::map<std::string, std::any>> updateItems) {
    _updateItems = updateItems;
}

std::map<int, std::map<std::string, std::any>> EntityManager::getUpdateItems() {
    return _updateItems;
}
