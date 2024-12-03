/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Implements the core client functionality, acting as the main controller.
** Responsible for managing the client's connection to the server and its lifecycle.
** Responsibility:
** - Initialize and maintain the client-server connection.
** - Handle communication with the server.
** - Manage the main client loop and update flow.
** Client.cpp
*/

#include "Client.hpp"

Client::Client() {}

Client::~Client() {}

void Client::manageClient() {

}

std::vector<std::shared_ptr<Entity>> Client::getEntities() {
    return(_entities);
}

void Client::setEntities(std::vector<std::shared_ptr<Entity>> &entities) {

}

std::vector<std::any> Client::getItems() {
    return (_items);
}

void Client::setItems(std::vector<std::any> items) {

}

void Client::createItems() {

}

void Client::drawAllItems() {

}

void Client::setPos() {

}

void Client::setText() {

}

void Client::setSprite() {

}

void Client::updateSprite() {

}