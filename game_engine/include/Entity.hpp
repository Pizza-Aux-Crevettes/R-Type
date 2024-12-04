/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Entity.hpp
*/

#pragma once

#include "components/Button.hpp"
#include "components/Components.hpp"

#include <iostream>
#include <vector>
#include <typeinfo>

namespace GameEngine {

class Entity {
  public:
    Entity();
    ~Entity();

    template <typename ComponentType>
    void addComponent(ComponentType&& component);

    template <typename ComponentType>
    void removeComponent();

    std::vector<std::unique_ptr<Component>>& getComponents();
    void displayComponents() const;
    int getEntityId() const;

  private:
    int _id;
    std::vector<std::unique_ptr<Component>> components;
};

template <typename ComponentType>
void Entity::addComponent(ComponentType&& component) {
    for (auto& tmpComponent : components) {
        auto& componentRef = *tmpComponent;
        if (typeid(componentRef) == typeid(ComponentType)) {
            std::cout << "Component already adding to the Entity"
                      << std::endl;
            return;
        }
    }
    components.push_back(std::make_unique<ComponentType>(
        std::forward<ComponentType>(component)));
}

template <typename ComponentType>
void Entity::removeComponent() {
    int index = 0;
    for (auto& tmpComponent : components) {
        auto& componentRef = *tmpComponent;
        if (typeid(componentRef) == typeid(ComponentType)) {
            components.erase(components.begin() + index);
            return;
        }
        index++;
    }
}

}; // namespace GameEngine