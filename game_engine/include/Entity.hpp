/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Entity.hpp
*/

#pragma once

#include "components/Button.hpp"
#include "components/Components.hpp"
#include <memory>
#include <typeindex>

namespace GameEngine {

class Entity {
  public:
    Entity();

    template <typename... Args> Entity(Args&&... args);

    ~Entity();

    template <typename ComponentType>
    void addComponent(ComponentType component);

    template <typename ComponentType> void removeComponent();

    template <typename ComponentType> ComponentType& getComponent();

    void displayComponents() const;
    int getEntityId() const;

  private:
    int _id;
    std::map<std::type_index, std::unique_ptr<Component>> _components;
};

template <typename... Args> Entity::Entity(Args&&... args) : _id(0) {
    (addComponent(std::forward<Args>(args)), ...);
}

template <typename ComponentType>
void Entity::addComponent(ComponentType component) {
    const auto component_found =
        _components.find(std::type_index(typeid(ComponentType)));
    if (component_found == _components.end()) {
        _components[std::type_index(typeid(ComponentType))] =
            std::make_unique<ComponentType>(component);
        return;
    }
    throw std::runtime_error(
        "GameEngine::Entity::addComponent: Component already exists");
}

template <typename ComponentType> void Entity::removeComponent() {
    const auto component_found =
        _components.find(std::type_index(typeid(ComponentType)));
    if (component_found == _components.end()) {
        throw std::runtime_error(
            "GameEngine::Entity::removeComponent: Component not found");
    }
    _components.erase(component_found);
}

template <typename ComponentType> ComponentType& Entity::getComponent() {
    const auto component_found =
        _components.find(std::type_index(typeid(ComponentType)));
    if (component_found == _components.end()) {
        throw std::runtime_error(
            "GameEngine::Entity::getComponent: Component not found");
    }
    return static_cast<ComponentType&>(*component_found->second);
}

}; // namespace GameEngine