/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Singletons.cpp
*/

#include "util/Singletons.hpp"
#include "util/Logger.hpp"

RoomManager& Singletons::getRoomManager() {
    Logger::debug("[Singletons] Accessed RoomManager instance.");

    return RoomManager::getInstance();
}

Protocol& Singletons::getProtocol() {
    Logger::debug("[Singletons] Accessed Protocol instance.");

    return Protocol::getInstance();
}
