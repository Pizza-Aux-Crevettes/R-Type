/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** This file declares the `EntityManager` class, responsible for managing the
** entity list.
** EntityManager.cpp
*/

#include "EntityManager.hpp"
#include "util/getResponsiveValue.hpp"

EntityManager::EntityManager() {}

EntityManager::~EntityManager() {}

EntityManager& EntityManager::get() {
    static EntityManager instance;
    return instance;
}

void EntityManager::setEntityList(std::map<int, GameEngine::Entity> entities) {
    _entities = entities;
}

std::map<int, GameEngine::Entity>& EntityManager::getEntityList() {
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
    if (components.size() > 0) {
        auto newEntity = GameEngine::Entity(id);

        auto textureIt = components.find("Texture");
        auto textureRectIt = components.find("TextureRect");
        auto sizeIt = components.find("Size");
        auto positionIt = components.find("Position");
        auto textLink = components.find("Link");

        if (textureIt != components.end()) {
            const auto& texture = textureIt->second;

            if (textureRectIt != components.end()) {
                const auto& textureRect = textureRectIt->second;

                if (sizeIt != components.end()) {
                    const auto& size = sizeIt->second;

                    newEntity.addComponent(
                        Shape(Rectangle,
                              std::any_cast<std::pair<float, float>>(size)));
                    newEntity.addComponent(
                        Texture(std::any_cast<std::string>(texture),
                                std::any_cast<std::vector<int>>(textureRect)));
                } else {
                    newEntity.addComponent(Sprite());
                    newEntity.addComponent(
                        Texture(std::any_cast<std::string>(texture),
                                std::any_cast<std::vector<int>>(textureRect)));
                }
            } else {
                newEntity.addComponent(Sprite());
                newEntity.addComponent(
                    Texture(std::any_cast<std::string>(texture)));
            }
        }

        if (positionIt != components.end()) {
            const auto& position = positionIt->second;
            try {
                newEntity.addComponent(Position(
                    {std::any_cast<std::pair<float, float>>(position)}));
            } catch (const std::bad_any_cast& e) {
                std::cerr << "Error casting Position component: " << e.what()
                          << std::endl;
            }
        }

        if (textLink != components.end()) {
            const auto& text = textLink->second;
            try {
                newEntity.addComponent(Text(std::any_cast<std::string>(text), "assets/font/Inter_Bold.ttf", 10));
                newEntity.addComponent(Link(std::any_cast<int>(id - 10000)));
            } catch (const std::bad_any_cast& e) {
                std::cerr << "Error casting Text or Link component: " << e.what()
                          << std::endl;
            }
        }

        _entities.emplace(id, std::move(newEntity));
    }
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

std::vector<int> EntityManager::getPlayerColor() {
    return _playerSpriteColor;
}

void EntityManager::setPlayerColor(int playerId) {
    

    int num = playerId % 5;

    switch(num) {
        case 1 :
            _playerSpriteColor = {0, 0, 34, 15};
            break;
        case 2 :
            _playerSpriteColor = {0, 34, 34, 15};
            break;
        case 3 :
            _playerSpriteColor = {0, 51, 34, 15};
            break;
        case 4 :
            _playerSpriteColor = {0, 68, 34, 15};
            break;
        case 5 :
            _playerSpriteColor = {0, 85, 34, 15};
            break;
        default:
            _playerSpriteColor = {0, 0, 34, 15};
            break;
    }
}

sf::Texture EntityManager::manageBackground(sf::RenderWindow& window) {
    GetResponsiveValue responsive;

    int id = 0;
    auto newEntity = GameEngine::Entity(id);
    newEntity.addComponent(
        Shape(ShapeType::Rectangle,
              {responsive.getResponsiveSizeX(800, window.getSize().x, 800),
               responsive.getResponsiveSizeY(600, window.getSize().y, 600)}));
    newEntity.addComponent(Texture("assets/sprite/space.png"));
    newEntity.addComponent(Position());
    sf::Texture& newTexture = newEntity.getComponent<Texture>().getTexture();
    newTexture.setRepeated(true);
    _entities.emplace(id, std::move(newEntity));

    return newTexture;
}

std::mutex& EntityManager::getMutex() {
    return _mutex;
}