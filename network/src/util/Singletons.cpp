/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Singletons.cpp
*/

#include "util/Singletons.hpp"

Server& Singletons::getServer() {
    return Server::getInstance();
}

RoomManager& Singletons::getRoomManager() {
    return RoomManager::getInstance();
}

PlayerManager& Singletons::getPlayerManager() {
    return PlayerManager::getInstance();
}

Protocol& Singletons::getProtocol() {
    return Protocol::getInstance();
}
