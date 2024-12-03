/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Client.hpp
*/

#pragma once

#include "Entity.hpp"
#include <memory>
#include <vector>
#include <any>

class Client {
  private:
    std::vector<std::shared_ptr<Entity>> _entities;
    std::vector<std::any> _items;

  public:
    Client();
    ~Client();
    void manageClient();
    void setEntities(std::vector<std::shared_ptr<Entity>> &entities);
    std::vector<std::shared_ptr<Entity>> getEntities();
    void setItems(std::vector<std::any> items);
    std::vector<std::any> getItems();
    void createItems();
    void drawAllItems();
    void setPos();
    void setText();
    void setSprite();
    void updateSprite();
};