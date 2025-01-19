/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** This file implements the Protocol class, which is responsible for handling
** network messages and interactions in the game. It processes different types of
** messages identified by opCodes, such as player creation, updates on players, 
** enemies, bullets, obstacles, and entity health.
** Protocol.cpp
*/

#include "network/protocol/Protocol.hpp"
#include <iostream>
#include "EntityManager.hpp"
#include "components/Sound.hpp"
#include "Client.hpp"
#include "util/Logger.hpp"
#include "health/LifeBar.hpp"

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

    case UPDATE_ENTITY_HEALTH:
        handleUpdateEntityHealth(smartBuffer);
        break;

    case UPDATE_PLAYER_INFOS:
        handleUpdatePlayerInfos(smartBuffer);
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

    EntityManager::get().setPlayerColor(playerId);
    std::vector<int> playerRect = EntityManager::get().getPlayerColor();
    Protocol::setPlayerId(playerId);
    LifeBar::get().setPlayerId(playerId);
    EntityManager::get().setPlayerId(playerId);

    std::map<std::string, std::any> newItems = {
        {"Texture", std::string("assets/sprite/spaceship.png")},
        {"TextureRect", std::vector<int>{playerRect}},
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

    EntityManager::get().setPlayerColor(playerId);
    std::vector<int> playerRect = EntityManager::get().getPlayerColor();

    std::map<std::string, std::any> newItems = {
        {"Texture", std::string("assets/sprite/spaceship.png")},
        {"TextureRect", std::vector<int>{playerRect}},
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
    std::string filePath = "";
    std::vector<int> rect;
    
    smartBuffer >> enemyId >> x >> y >> width >> height >> type;

    if (type == 1) {
        filePath = "assets/sprite/mob1.gif";
        rect = EntityManager::get().setEnemy(1);
    } else if (type == 2) {
        filePath = "assets/sprite/mob2.gif";
        rect = EntityManager::get().setEnemy(2);
    } else if (type == 3) {
        filePath = "assets/sprite/mob3.png";
        rect = EntityManager::get().setEnemy(3);
    } else if (type == 4) {
        filePath = "assets/sprite/mob4.gif";
        rect = EntityManager::get().setEnemy(4);
    } else if (type == 4) {
        filePath = "assets/sprite/mob4.gif";
        rect = EntityManager::get().setEnemy(4);
    } else if (type == 5) {
        filePath = "assets/sprite/boss.gif";
        rect = EntityManager::get().setEnemy(5);
        EntityManager::get().setBossId(enemyId);
    }
    
    std::vector<int> rectVector = {0, 0, 66, 57};
    std::map<std::string, std::any> newItems = {
        {"Texture", filePath},
        {"TextureRect", rect},
        {"Size", std::pair<float, float>(width, height)},
        {"Position", std::pair<float, float>(x, y)}};
    EntityManager::get().CompareEntities(enemyId, newItems, {x, y});
}

void Protocol::handleUpdatePlayerInfos(SmartBuffer& smartBuffer) {
    int32_t playerId, score;
    int16_t kills;
    
    smartBuffer >> playerId >> kills >> score;
}

void Protocol::handleUpdateBullets(SmartBuffer& smartBuffer) {
    int32_t bulletId, x, y;
    int16_t type;
    std::string texture = std::string("assets/sprite/shoot_blue.png");
    std::vector<int> textureRect = {180, 0, 50, 20};
    
    smartBuffer >> bulletId >> x >> y >> type;

    if (type > 0) {
        texture = std::string("assets/sprite/shoot_yellow.png");
        textureRect = {35, 0, 50, 20};
    }
    std::map<std::string, std::any> newItems = {
        {"Texture", texture},
        {"TextureRect", textureRect},
        {"Position", std::pair<float, float>(x, y)}};
    EntityManager::get().CompareEntities(bulletId, newItems, {x, y});
}

void Protocol::handleDeleteEntity(SmartBuffer& smartBuffer) {
    int32_t entityId;
    
    smartBuffer >> entityId;
	std::lock_guard<std::mutex> guard(EntityManager::get().getMutex());
    auto& _entities = EntityManager::get().getEntityList();

	if (_entities.empty()) {
    	return;
	}

    if (auto search = _entities.find(entityId); search != _entities.end()) {
        if (auto search = _entities.find(entityId + 10000); search != _entities.end()) {
            _entities.erase(entityId + 10000);
        }
        _entities.erase(entityId);
    }
}

void Protocol::handleUpdateEntityHealth(SmartBuffer& smartBuffer) {
    int32_t entityId;
    int16_t health, maxHealth;
    smartBuffer >> entityId >> health >> maxHealth;
    LifeBar::get().manageHealth(entityId, health);
    EntityManager::get().winGame(entityId, health);
    EntityManager::get().loseGame(entityId, health);
}
