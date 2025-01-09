/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Protocol.cpp
*/

#include "protocol/Protocol.hpp"
#include <iostream>
#include "EntityManager.hpp"

int32_t Protocol::_playerId = -1;

Protocol& Protocol::get() {
    static Protocol instance;
    return instance;
}

Protocol::Protocol() {}

Protocol::~Protocol() {}

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
    case DEFAULT:
        handleDefault(smartBuffer);
        break;
    case NEW_PLAYER_CALLBACK:
        handleNewPlayerCallback(smartBuffer);
        break;
    case NEW_PLAYER_BROADCAST:
        handleNewPlayerBroadcast(smartBuffer);
        break;
    case PLAYER_POSITION_UPDATE:
        handlePlayerUpdatePosition(smartBuffer);
        break;
    case PLAYER_LIFE_UPDATE:
        handlePlayerUpdateLife(smartBuffer);
        break;
    case MAP_VIEWPORT_UPDATE:
        handleViewportUpdate(smartBuffer);
        break;
    case MAP_OBSTACLES_UPDATE:
        handleBlocksUpdate(smartBuffer);
        break;
    default:
        std::cerr << "[Protocol] Unknown OpCode received: " << opCode
                  << std::endl;
        break;
    }
}

void Protocol::handleDefault(SmartBuffer& smartBuffer) {
    std::string test;

    smartBuffer >> test;

    std::cout << "[Protocol] DEFAULT - Test: " << test << std::endl;

    // Debug
    // Init le UDP sur le serveur
    // Ne pas toucher
}

void Protocol::handleNewPlayerCallback(SmartBuffer& smartBuffer) {
    int32_t playerId;

    smartBuffer >> playerId;
    Protocol::setPlayerId(playerId);

    std::cout << "[Protocol] NEW_PLAYER_CALLBACK - Player ID: " << playerId
              << std::endl;

    // Cette fonction renvoi l'id du joueur créé. (Toujours son propre ID)
    // Important pour savoir quel joueur est le notre.
    std::map<std::string, std::any> newItems = {
        {{"Texture", std::string("assets/sprite/spaceship.png")},
         {"TextureRect", std::vector<int>{0, 0, 34, 15}},
         {"Position", std::pair<float, float>(0.0f, 0.0f)}}};

    EntityManager::get().CompareEntities(playerId, newItems, {0.0f, 0.0f});
}

void Protocol::handleNewPlayerBroadcast(SmartBuffer& smartBuffer) {
    int32_t playerId;
    std::string playerName;

    smartBuffer >> playerId >> playerName;

    std::cout << "[Protocol] NEW_PLAYER_BROADCAST - Player ID: " << playerId
              << ", Player Name: " << playerName << std::endl;

    // Un joueur a été créé.
    // On ajoute le joueur à la liste des joueurs connectés
    // La donnée est envoyée à tous les joueurs connectés

    std::map<std::string, std::any> newItems = {
        {{"Texture", std::string("assets/sprite/spaceship.png")},
         {"TextureRect", std::vector<int>{0, 0, 34, 15}},
         {"Position", std::pair<float, float>(0.0f, 0.0f)}}};

    EntityManager::get().CompareEntities(playerId, newItems, {0.0f, 0.0f});
}

void Protocol::handlePlayerUpdatePosition(SmartBuffer& smartBuffer) {
    int32_t playerId;
    double x, y;

    smartBuffer >> playerId >> x >> y;

    // Cette fonction renvoi la position du joueur
    // On met à jour la position du joueur

    std::map<std::string, std::any> emptyMap;
    EntityManager::get().CompareEntities(playerId, emptyMap, {x, y});
}

void Protocol::handlePlayerUpdateLife(SmartBuffer& smartBuffer) {
    int32_t playerId;
    double life;

    smartBuffer >> playerId >> life;

    std::cout << "[Protocol] PLAYER_LIFE_UPDATE - Player ID: " << playerId
              << ", Life: " << life << std::endl;

    // Cette fonction renvoi la vie du joueur
    // On met à jour la vie du joueur
}

void Protocol::handleViewportUpdate(SmartBuffer& smartBuffer) {
    int32_t viewport;

    smartBuffer >> viewport;

    std::cout << "[Protocol] MAP_VIEWPORT_UPDATE - Viewport: " << viewport
              << std::endl;

    // Cette fonction renvoi le viewport
    // On met à jour le viewport
    // Anastasia doit ici prendre la valeur du viewport et la mettre dans sa
    // fonction d'update du background (supprimer la clock elapsed time)
}

void Protocol::handleBlocksUpdate(SmartBuffer& smartBuffer) {
    int16_t x, y, type;

    smartBuffer >> x >> y >> type;

    std::cout << "[Protocol] MAP_OBSTACLES_UPDATE - X: " << x << ", Y: " << y
              << ", Type: " << type << std::endl;

    // Cette fonction renvoi les blocks visibles à l'écran en boucle, les blocks
    // NON envoyés sont supprimés Le serveur va renvoyer block par block les
    // blocks visibles à l'écran, si un block n'est pas envoyé, il est supprimé
    // Donc a tout les ticks, tout les blocks sont envoyés un a un
}
