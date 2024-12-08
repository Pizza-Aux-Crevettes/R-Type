/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Singletons.cpp
*/

#include "util/Singletons.hpp"
#include "util/Logger.hpp"

RoomManager& Singletons::getRoomManager() {
    return RoomManager::getInstance();
}

Protocol& Singletons::getProtocol() {
    return Protocol::getInstance();
}
