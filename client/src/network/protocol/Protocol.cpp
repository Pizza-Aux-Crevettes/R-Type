/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Protocol.cpp
*/

#include "network/protocol/Protocol.hpp"
#include <iostream>
#include "EntityManager.hpp"
#include "util/Logger.hpp"

int32_t Protocol::_playerId = -1;

Protocol& Protocol::get() {
    static Protocol instance;
    return instance;
}

int32_t Protocol::getPlayerId() {
    return _playerId;
}

void Protocol::setPlayerId(int32_t playerId) {
    _playerId = playerId;
}

void Protocol::handleMessage(SmartBuffer& smartBuffer) {
    int16_t opCode;
    smartBuffer >> opCode;

    switch (opCode) {

    case NEW_PLAYER_CALLBACK:
        handleNewPlayerCallback(smartBuffer);
        break;

    case NEW_PLAYER_BROADCAST:
        handleNewPlayerBroadcast(smartBuffer);
        break;

    case PLAYERS_UPDATE:
        handlePlayerUpdatePosition(smartBuffer);
        break;

    case PLAYER_DELETED:
        handlePlayerDeleted(smartBuffer);
        break;

    case VIEWPORT_UPDATE:
        handleViewportUpdate(smartBuffer);
        break;

    case OBSTACLES_UPDATE:
        handleBlocksUpdate(smartBuffer);
        break;

    case OBSTACLE_DELETED:
        handleBlockDeleted(smartBuffer);
        break;

    case BULLETS_UPDATE:
        handleBulletsUpdate(smartBuffer);
        break;

    case BULLET_DELETED:
        handleBulletDeleted(smartBuffer);
        break;

    default:
        Logger::error("[Protocol] Unknown OpCode received: " +
                      std::to_string(opCode));
        break;
    }
}

void Protocol::handleNewPlayerCallback(SmartBuffer& smartBuffer) {
    int32_t playerId;
    smartBuffer >> playerId;

    Protocol::setPlayerId(playerId);

    Logger::success("[Protocol] NEW_PLAYER_CALLBACK - Assigned Player ID: " +
                    std::to_string(playerId));

    Logger::success("[Protocol] NEW_PLAYER_CALLBACK - Assigned Player ID: " +
                    std::to_string(playerId));

    std::map<std::string, std::any> newItems = {
        {"Texture", std::string("assets/sprite/spaceship.png")},
        {"TextureRect", std::vector<int>{0, 0, 34, 15}},
        {"Position", std::pair<float, float>(0.0f, 0.0f)}};

    EntityManager::get().CompareEntities(playerId, newItems, {0.0f, 0.0f});
}

void Protocol::handleNewPlayerBroadcast(SmartBuffer& smartBuffer) {
    int32_t playerId;
    std::string playerName;

    smartBuffer >> playerId >> playerName;

    std::map<std::string, std::any> newItems = {
        {"Texture", std::string("assets/sprite/spaceship.png")},
        {"TextureRect", std::vector<int>{0, 0, 34, 15}},
        {"Position", std::pair<float, float>(0.0f, 0.0f)}};

    EntityManager::get().CompareEntities(playerId, newItems, {0.0f, 0.0f});
}

void Protocol::handlePlayerUpdatePosition(SmartBuffer& smartBuffer) {
    int32_t playerId, x, y;
    smartBuffer >> playerId >> x >> y;

    std::map<std::string, std::any> emptyMap;
    EntityManager::get().CompareEntities(playerId, emptyMap, {x, y});
}

void Protocol::handlePlayerDeleted(SmartBuffer& smartBuffer) {
    int32_t playerId;
    smartBuffer >> playerId;

    // Logger::info("[Protocol] PLAYER_DELETED\n"
    //              "  -> Deleted Player ID: " + std::to_string(playerId));
}

void Protocol::handleViewportUpdate(SmartBuffer& smartBuffer) {
    double viewport;
    smartBuffer >> viewport;

    // Logger::info("[Protocol] VIEWPORT_UPDATE\n"
    //              "  -> Updated Viewport: " + std::to_string(viewport));

    Client::get().setViewport(viewport);
}

void Protocol::handleBlocksUpdate(SmartBuffer& smartBuffer) {
    int32_t obstacleId, x, y;
    int16_t type, size;
    smartBuffer >> obstacleId >> x >> y >> size >> type;

    Logger::info("[Protocol] MAP_OBSTACLES_UPDATE - Obstacle ID: " +
                 std::to_string(obstacleId) + ", Position: (" +
                 std::to_string(x) + ", " + std::to_string(y) +
                 "), Type: " + std::to_string(type));

    std::map<std::string, std::any> newItems = {
        {"Texture", std::string("assets/sprite/obstacle.png")},
        {"TextureRect", std::vector<int>{0, 0, 150, 30}},
        {"Size", std::pair<float, float>(size, size)},
        {"Position", std::pair<float, float>(x, y)}};
    EntityManager::get().CompareEntities(obstacleId, newItems, {x, y});
}

void Protocol::handleBlockDeleted(SmartBuffer& smartBuffer) {
    int32_t obstacleId;
    smartBuffer >> obstacleId;

    // Logger::info("[Protocol] OBSTACLE_DELETED\n"
    //              "  -> Deleted Obstacle ID: " + std::to_string(obstacleId));
}

void Protocol::handleBulletsUpdate(SmartBuffer& smartBuffer) {
    int32_t bulletId, x, y;
    smartBuffer >> bulletId >> x >> y;

    std::map<std::string, std::any> newItems = {
        {"Texture", std::string("assets/sprite/shoot_blue.png")},
        {"Position", std::pair<float, float>(x, y)}};

    EntityManager::get().CompareEntities(bulletId, newItems, {x, y});
}

void Protocol::handleBulletDeleted(SmartBuffer& smartBuffer) {
    int32_t bulletId;
    smartBuffer >> bulletId;

    // Logger::info("[Protocol] BULLET_DELETED\n"
    //              "  -> Deleted Bullet ID: " + std::to_string(bulletId));
}
