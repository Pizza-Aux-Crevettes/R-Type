/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Protocol.cpp
*/

#include "network/protocol/Protocol.hpp"
#include <iostream>
#include "EntityManager.hpp"
#include "components/Sound.hpp"
#include "Client.hpp"
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

    case CREATE_PLAYER_CALLBACK:
        handleCreatePlayerCallback(smartBuffer);
        break;

    case CREATE_PLAYER_BROADCAST:
        handleCreatePlayerBroadcast(smartBuffer);
        break;

    case UPDATE_PLAYERS:
        handleUpdatePlayer(smartBuffer);
        break;

    case UPDATE_VIEWPORT:
        handleUpdateViewport(smartBuffer);
        break;

    case UPDATE_OBSTACLES:
        handleUpdateBlocks(smartBuffer);
        break;

    case UPDATE_BULLETS:
        handleUpdateBullets(smartBuffer);
        break;

    case UPDATE_ENEMIES:
        handleUpdateEnemies(smartBuffer);
        break;

    case DELETE_ENTITY:
        handleDeleteEntity(smartBuffer);
        break;

    default:
        Logger::error("[Protocol] Unknown OpCode received: " +
                      std::to_string(opCode));
        break;
    }
}

void Protocol::handleCreatePlayerCallback(SmartBuffer& smartBuffer) {
    int32_t playerId;
    int16_t width, height;
    
    smartBuffer >> playerId >> width >> height;

    Protocol::setPlayerId(playerId);

    std::map<std::string, std::any> newItems = {
        {"Texture", std::string("assets/sprite/spaceship.png")},
        {"TextureRect", std::vector<int>{0, 0, 34, 15}},
        {"Position", std::pair<float, float>(0.0f, 0.0f)}};

    std::map<std::string, std::any> playerNameItems = {
        {"Link", std::string(Client::get().getUsername())},
        {"Position", std::pair<float, float>(0.0f, -10.0f)}
    };

    EntityManager::get().CompareEntities(playerId, newItems, {0.0f, 0.0f});
    EntityManager::get().CompareEntities(playerId + 10000, playerNameItems, {0.0f, 00.0f});
}

void Protocol::handleCreatePlayerBroadcast(SmartBuffer& smartBuffer) {
    int32_t playerId;
    std::string playerName;
    int16_t width, height;

    smartBuffer >> playerId >> playerName >> width >> height;

    std::map<std::string, std::any> newItems = {
        {"Texture", std::string("assets/sprite/spaceship.png")},
        {"TextureRect", std::vector<int>{0, 0, 34, 15}},
        {"Position", std::pair<float, float>(0.0f, 0.0f)}};

    std::map<std::string, std::any> playerNameItems = {
        {"Link", std::string(playerName)},
        {"Position", std::pair<float, float>(0.0f, -10.0f)}
    };

    EntityManager::get().CompareEntities(playerId, newItems, {0.0f, 0.0f});
    EntityManager::get().CompareEntities(playerId + 10000, playerNameItems, {00.0f, -10.0f});
}

void Protocol::handleUpdatePlayer(SmartBuffer& smartBuffer) {
    int32_t playerId, x, y;
    
    smartBuffer >> playerId >> x >> y;

    std::map<std::string, std::any> emptyMap;
    EntityManager::get().CompareEntities(playerId, emptyMap, {x, y});
}

void Protocol::handleUpdateViewport(SmartBuffer& smartBuffer) {
    double viewport;
    
    smartBuffer >> viewport;

    Client::get().setViewport(viewport);
}

void Protocol::handleUpdateBlocks(SmartBuffer& smartBuffer) {
    int32_t obstacleId, x, y;
    int16_t type, size;
    
    smartBuffer >> obstacleId >> x >> y >> size >> type;
    
    std::vector<int> rectVector = {0, 0, 50, 60};

    if (type == 1) {
        rectVector = {0, 0, 50, 60};
    } else if (type == 2) {
        rectVector = {130, 70, 60, 60};
    } else if (type == 3) {
        rectVector = {130, 130, 50, 60};
    } else if (type == 4) {
        rectVector = {130, 0, 60, 60};
    }

    std::map<std::string, std::any> newItems = {
        {"Texture", std::string("assets/sprite/asteroids_8.png")},
        {"TextureRect", std::vector<int>{rectVector}},
        {"Size", std::pair<float, float>(size, size)},
        {"Position", std::pair<float, float>(x, y)}};
    EntityManager::get().CompareEntities(obstacleId, newItems, {x, y});
}

void Protocol::handleUpdateEnemies(SmartBuffer& smartBuffer) {
    int32_t enemyId, x, y;
    int16_t type, width, height;
    
    smartBuffer >> enemyId >> x >> y >> width >> height >> type;
    
    std::vector<int> rectVector = {0, 0, 66, 57};
    std::map<std::string, std::any> newItems = {
        {"Texture", std::string("assets/sprite/enemy.png")},
        {"TextureRect", std::vector<int>{rectVector}},
        {"Size", std::pair<float, float>(width, height)},
        {"Position", std::pair<float, float>(x, y)}};
    EntityManager::get().CompareEntities(enemyId, newItems, {x, y});

    Logger::info("[Protocol] Updating enemy: " + std::to_string(enemyId));
}

void Protocol::handleUpdateBullets(SmartBuffer& smartBuffer) {
    int32_t bulletId, x, y;
    
    smartBuffer >> bulletId >> x >> y;

    std::map<std::string, std::any> newItems = {
        {"Texture", std::string("assets/sprite/shoot_blue.png")},
        {"TextureRect", std::vector<int>{180, 0, 50, 20}},
        {"Position", std::pair<float, float>(x, y)}};
    EntityManager::get().CompareEntities(bulletId, newItems, {x, y});
}

void Protocol::handleDeleteEntity(SmartBuffer& smartBuffer) {
    int32_t entityId;
    
    smartBuffer >> entityId;

    //Logger::info("[Protocol] Deleting entity: " + std::to_string(entityId));

    auto& _entities = EntityManager::get().getEntityList();

	if (_entities.empty()) {
    	return;
	}

    if (auto search = _entities.find(entityId); search != _entities.end()) {
        _entities.erase(entityId);
    }
}
