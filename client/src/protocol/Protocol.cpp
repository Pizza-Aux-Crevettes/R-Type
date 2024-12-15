/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Protocol.cpp
*/

#include "protocol/Protocol.hpp"
#include <iostream>

Protocol& Protocol::get() {
    static Protocol instance;
    return instance;
}

Protocol::Protocol() {}

Protocol::~Protocol() {}

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
        handleNewPlayerBroadcast(smartBuffer);
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

void Protocol::handleNewPlayerBroadcast(SmartBuffer& smartBuffer) {
    int32_t playerId;
    std::string playerName;
    smartBuffer >> playerId >> playerName;
    std::cout << "[Protocol] NEW_PLAYER_BROADCAST - Player ID: " << playerId
              << ", Player Name: " << playerName << std::endl;
    // Ici tu créé un nouveau player en pos 0 0 (on fera au propre plus tard)
}

void Protocol::handlePlayerUpdatePosition(SmartBuffer& smartBuffer) {
    int32_t playerId;
    double x, y;
    smartBuffer >> playerId >> x >> y;
    std::cout << "[Protocol] PLAYER_UPDATE_POSITION - Player ID: " << playerId
              << ", X: " << x << ", Y: " << y << std::endl;
    // Ici tu update le player avec son ID et tu met a jour ses positions X et Y 0 (on fera au propre plus tard)
}
