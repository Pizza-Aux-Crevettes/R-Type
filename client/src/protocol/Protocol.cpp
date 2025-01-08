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
    case CREATE_ROOM_CALLBACK:
        handleCreateRoomCallback(smartBuffer);
        break;
    case LEAVE_ROOM_CALLBACK:
        handleLeaveRoomCallback(smartBuffer);
        break;
    case JOIN_ROOM_CALLBACK:
        handleJoinRoomCallback(smartBuffer);
        break;
    case DELETE_ROOM_CALLBACK:
        handleDeleteRoomCallback(smartBuffer);
        break;
    case NEW_PLAYER_CALLBACK:
        handleNewPlayerCallback(smartBuffer);
        break;
    case START_GAME_CALLBACK:
        handleStartGameCallback(smartBuffer);
        break;
    case STOP_GAME_CALLBACK:
        handleStopGameCallback(smartBuffer);
        break;
    case CREATE_ROOM_BROADCAST:
        handleCreateRoomBroadcast(smartBuffer);
        break;
    case LEAVE_ROOM_BROADCAST:
        handleLeaveRoomBroadcast(smartBuffer);
        break;
    case JOIN_ROOM_BROADCAST:
        handleJoinRoomBroadcast(smartBuffer);
        break;
    case DELETE_ROOM_BROADCAST:
        handleDeleteRoomBroadcast(smartBuffer);
        break;
    case NEW_PLAYER_BROADCAST:
        handleNewPlayerBroadcast(smartBuffer);
        break;
    case START_GAME_BROADCAST:
        handleStartGameBroadcast(smartBuffer);
        break;
    case STOP_GAME_BROADCAST:
        handleStopGameBroadcast(smartBuffer);
        break;
    case PLAYER_UPDATE_POSITION:
        handlePlayerUpdatePosition(smartBuffer);
        break;
    default:
        std::cerr << "[Protocol] Unknown OpCode received: " << opCode
                  << std::endl;
        break;
    }
}

//
//
// DEFAULT
//
//
void Protocol::handleDefault(SmartBuffer& smartBuffer) {
    std::string test;

    smartBuffer >> test;

    std::cout << "[Protocol] DEFAULT - Test: " << test << std::endl;

    // Debug
    // Init le UDP sur le serveur
    // Ne pas toucher
}

//
//
// CALLBACKS
//
//
void Protocol::handleCreateRoomCallback(SmartBuffer& smartBuffer) {
    int16_t statusCode;
    std::string roomCode;

    smartBuffer >> statusCode >> roomCode;

    std::cout << "[Protocol] CREATE_ROOM_CALLBACK - Status Code: " << statusCode
              << std::endl;

    // Cette fonction renvoi un status code et le code de la room pour savoir si
    // la room a bien été créée. Voir la doc du protocol pour comprendre les
    // codes erreurs Important pour afficher le code à l'écran du joueur qui a
    // créé la room
}

void Protocol::handleLeaveRoomCallback(SmartBuffer& smartBuffer) {
    int16_t statusCode;

    smartBuffer >> statusCode;

    std::cout << "[Protocol] LEAVE_ROOM_CALLBACK - Status Code: " << statusCode
              << std::endl;

    // Cette fonction renvoi un status code pour savoir si la room a bien été
    // quittée. Voir la doc du protocol pour comprendre les codes erreurs
}

void Protocol::handleJoinRoomCallback(SmartBuffer& smartBuffer) {
    int16_t statusCode;

    smartBuffer >> statusCode;

    std::cout << "[Protocol] JOIN_ROOM_CALLBACK - Status Code: " << statusCode
              << std::endl;

    // Cette fonction renvoi un status code pour savoir si la room a bien été
    // rejoins. Voir la doc du protocol pour comprendre les codes erreurs
}

void Protocol::handleDeleteRoomCallback(SmartBuffer& smartBuffer) {
    int16_t statusCode;

    smartBuffer >> statusCode;

    std::cout << "[Protocol] DELETE_ROOM_CALLBACK - Status Code: " << statusCode
              << std::endl;

    // Cette fonction renvoi un status code pour savoir si la room a bien été
    // supprimée. Voir la doc du protocol pour comprendre les codes erreurs
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

void Protocol::handleStartGameCallback(SmartBuffer& smartBuffer) {
    int16_t statusCode;

    smartBuffer >> statusCode;

    std::cout << "[Protocol] START_GAME_CALLBACK - Status Code: " << statusCode
              << std::endl;

    // Cette fonction renvoi un status code pour savoir si la partie est bien
    // lancée. Voir la doc du protocol pour comprendre les codes erreurs
    // Afficher un petit popup à l'écran du joueur pour lui dire que la partie
    // est BIEN lancée (ex: Vous avez lancée la partie)
}

void Protocol::handleStopGameCallback(SmartBuffer& smartBuffer) {
    int16_t statusCode;

    smartBuffer >> statusCode;

    std::cout << "[Protocol] STOP_GAME_CALLBACK - Status Code: " << statusCode
              << std::endl;

    // Cette fonction renvoi un status code pour savoir si la partie a bien été
    // stoppée. Voir la doc du protocol pour comprendre les codes erreurs
    // Afficher un petit popup à l'écran du joueur pour lui dire que la partie
    // est BIEN terminée (ex: Vous avez stoppée la partie)
}

//
//
// BROADCASTS
//
//
void Protocol::handleCreateRoomBroadcast(SmartBuffer& smartBuffer) {
    std::string roomCode;

    smartBuffer >> roomCode;

    std::cout << "[Protocol] CREATE_ROOM_BROADCAST - Room Code: " << roomCode
              << std::endl;

    // Une room a été créée.
    // Permet d'afficher la nouvelle room dans la liste des rooms disponibles
    // La donnée est envoyée à tous les joueurs connectés
}

void Protocol::handleLeaveRoomBroadcast(SmartBuffer& smartBuffer) {
    std::string roomCode;
    int32_t playerId;

    smartBuffer >> roomCode >> playerId;

    std::cout << "[Protocol] LEAVE_ROOM_BROADCAST - Room Code: " << roomCode
              << ", Player ID: " << playerId << std::endl;

    // Un joueur a quitté une room.
    // On décrémente le nombre de joueurs dans la room (exemple: c'était marqué
    // 5/10, maintenant c'est 4/10) La donnée est envoyée à tous les joueurs
    // connectés
}

void Protocol::handleJoinRoomBroadcast(SmartBuffer& smartBuffer) {
    std::string roomCode;
    int32_t playerId;

    smartBuffer >> roomCode >> playerId;

    std::cout << "[Protocol] JOIN_ROOM_BROADCAST - Room Code: " << roomCode
              << ", Player ID: " << playerId << std::endl;

    // Un joueur a rejoint une room.
    // On incrémente le nombre de joueurs dans la room (exemple: c'était marqué
    // 5/10, maintenant c'est 6/10) La donnée est envoyée à tous les joueurs
    // connectés
}

void Protocol::handleDeleteRoomBroadcast(SmartBuffer& smartBuffer) {
    std::string roomCode;

    smartBuffer >> roomCode;

    std::cout << "[Protocol] DELETE_ROOM_BROADCAST - Room Code: " << roomCode
              << std::endl;

    // Un joueur a supprimé une room.
    // On retire la room de la liste des rooms disponibles
    // La donnée est envoyée à tous les joueurs connectés
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

void Protocol::handleStartGameBroadcast(SmartBuffer& smartBuffer) {
    std::cout << "[Protocol] START_GAME_BROADCAST - Triggered " << std::endl;
    // Rien n'est envoyé au client, juste pour avertir.
    // Utile pour afficher un popup sur l'écran de tout les joeurs pour dire que
    // la partie est lancée La donnée est envoyée à tous les joueurs connectés
}

void Protocol::handleStopGameBroadcast(SmartBuffer& smartBuffer) {
    std::cout << "[Protocol] STOP_GAME_BROADCAST - Triggered " << std::endl;
    // Rien n'est envoyé au client, juste pour avertir.
    // Utile pour afficher un popup sur l'écran de tout les joeurs pour dire que
    // la partie est terminée La donnée est envoyée à tous les joueurs connectés
}

//
//
// REAL TIME UPDATES
//
//
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

    std::cout << "[Protocol] PLAYER_UPDATE_LIFE - Player ID: " << playerId
              << ", Life: " << life << std::endl;

    // Cette fonction renvoi la vie du joueur
    // On met à jour la vie du joueur
}

void Protocol::handleViewportUpdate(SmartBuffer& smartBuffer) {
    int32_t viewport;

    smartBuffer >> viewport;

    std::cout << "[Protocol] VIEWPORT_UPDATE - Viewport: " << viewport
              << std::endl;

    // Cette fonction renvoi le viewport
    // On met à jour le viewport
    // Anastasia doit ici prendre la valeur du viewport et la mettre dans sa
    // fonction d'update du background (supprimer la clock elapsed time)
}

void Protocol::handleBlocksUpdate(SmartBuffer& smartBuffer) {
    int16_t x, y, type;

    smartBuffer >> x >> y >> type;

    std::cout << "[Protocol] BLOCKS_UPDATE - X: " << x << ", Y: " << y
              << ", Type: " << type << std::endl;

    // Cette fonction renvoi les blocks visibles à l'écran en boucle, les blocks
    // NON envoyés sont supprimés Le serveur va renvoyer block par block les
    // blocks visibles à l'écran, si un block n'est pas envoyé, il est supprimé
    // Donc a tout les ticks, tout les blocks sont envoyés un a un
}
