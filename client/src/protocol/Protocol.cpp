/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Protocol.cpp
*/

#include <iostream>
#include "protocol/Protocol.hpp"

Protocol& Protocol::get() {
    static Protocol instance;
    return instance;
}

Protocol::Protocol() {}

Protocol::~Protocol() {}

void Protocol::handleMessage(SmartBuffer& smartBuffer, Client *client) {
    int16_t opCode;
    smartBuffer >> opCode;

    switch (opCode) {
    case DEFAULT:
        handleDefault(smartBuffer);
        break;
    case CREATE_ROOM_CALLBACK:
        handleCreateRoomCallback(smartBuffer);
        break;
    case CREATE_ROOM_BROADCAST:
        handleCreateRoomBroadcast(smartBuffer);
        break;
    case JOIN_ROOM_CALLBACK:
        handleJoinRoomCallback(smartBuffer);
        break;
    case JOIN_ROOM_BROADCAST:
        handleJoinRoomBroadcast(smartBuffer);
        break;
    case DELETE_ROOM_CALLBACK:
        handleDeleteRoomCallback(smartBuffer);
        break;
    case DELETE_ROOM_BROADCAST:
        handleDeleteRoomBroadcast(smartBuffer);
        break;
    case NEW_PLAYER_BROADCAST:
        handleNewPlayerBroadcast(smartBuffer, client);
        break;
    case PLAYER_UPDATE_POSITION:
        handlePlayerUpdatePosition(smartBuffer, client);
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
}

void Protocol::handleCreateRoomCallback(SmartBuffer& smartBuffer) {
    int16_t statusCode;
    smartBuffer >> statusCode;
    std::cout << "[Protocol] CREATE_ROOM_CALLBACK - Status Code: " << statusCode
              << std::endl;
}

void Protocol::handleCreateRoomBroadcast(SmartBuffer& smartBuffer) {
    std::string roomCode;
    smartBuffer >> roomCode;
    std::cout << "[Protocol] CREATE_ROOM_BROADCAST - Room Code: " << roomCode
              << std::endl;
}

void Protocol::handleJoinRoomCallback(SmartBuffer& smartBuffer) {
    int16_t statusCode;
    smartBuffer >> statusCode;
    std::cout << "[Protocol] JOIN_ROOM_CALLBACK - Status Code: " << statusCode
              << std::endl;
}

void Protocol::handleJoinRoomBroadcast(SmartBuffer& smartBuffer) {
    std::string roomCode;
    int32_t playerId;
    smartBuffer >> roomCode >> playerId;
    std::cout << "[Protocol] JOIN_ROOM_BROADCAST - Room Code: " << roomCode
              << ", Player ID: " << playerId << std::endl;
}

void Protocol::handleDeleteRoomCallback(SmartBuffer& smartBuffer) {
    int16_t statusCode;
    smartBuffer >> statusCode;
    std::cout << "[Protocol] DELETE_ROOM_CALLBACK - Status Code: " << statusCode
              << std::endl;
}

void Protocol::handleDeleteRoomBroadcast(SmartBuffer& smartBuffer) {
    std::string roomCode;
    smartBuffer >> roomCode;
    std::cout << "[Protocol] DELETE_ROOM_BROADCAST - Room Code: " << roomCode
              << std::endl;
}

void Protocol::handleNewPlayerBroadcast(SmartBuffer& smartBuffer, Client *client) {
    int32_t playerId;
    std::string playerName;
    smartBuffer >> playerId >> playerName;
    std::cout << "[Protocol] NEW_PLAYER_BROADCAST - Player ID: " << playerId
              << ", Player Name: " << playerName << std::endl;
    std::map<int, std::map<std::string, std::any>> newItems = {
        {playerId,
         {
             {"Texture", std::string("../assets/sprite/tentacles.png")},
            {"Position", std::pair<float, float>(0.0f, 0.0f)}
         }
        },
    };
    client->addItem(newItems);
}

void Protocol::handlePlayerUpdatePosition(SmartBuffer& smartBuffer, Client* client) {
    int32_t playerId;
    float x, y;
    smartBuffer >> playerId >> x >> y;

    // Check if the player exists in the local map
    if (_playerPositions.find(playerId) == _playerPositions.end()) {
        // Automatically create the player if not found
        Logger::info("[Protocol] Creating new player entry for Player ID: " + std::to_string(playerId));
        _playerPositions[playerId] = std::make_pair(0.0f, 0.0f); // Default starting position

        // Add the player to the client as well
        std::map<int, std::map<std::string, std::any>> newPlayer = {
            {playerId,
             {{"Texture", std::string("../assets/sprite/tentacles.png")},
              {"Position", std::make_pair(0.0f, 0.0f)}}}};
        client->addItem(newPlayer);

        Logger::success("[Protocol] Player " + std::to_string(playerId) +
                        " created with default position (0,0).");
    }

    // Update the player's position
    _playerPositions[playerId] = std::make_pair(x, y);

    // Update the client-side map for rendering
    std::map<int, std::map<std::string, std::any>> updateItems = {
        {playerId, {{"Position", std::make_pair(x, y)}}}};
    client->updateItem(updateItems);

    Logger::info("[Protocol] Updated Player Position - Player ID: " + std::to_string(playerId) +
                 ", X: " + std::to_string(x) + ", Y: " + std::to_string(y));
}
