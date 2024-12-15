#include <iostream>
#include "protocol/Protocol.hpp"
#include "util/Logger.hpp"
#include <mutex>

std::unordered_map<int32_t, std::pair<float, float>> Protocol::_playerPositions;
std::mutex Protocol::_playerPositionsMutex;

Protocol& Protocol::get() {
    static Protocol instance;
    return instance;
}

Protocol::Protocol() {}

Protocol::~Protocol() {}

void Protocol::handleMessage(SmartBuffer& smartBuffer, Client* client) {
    if (!client) {
        Logger::error("[Protocol] Null Client pointer passed to handleMessage.");
        return;
    }

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
        Logger::warning("[Protocol] Unknown OpCode received: " + std::to_string(opCode));
        break;
    }
}

void Protocol::handleDefault(SmartBuffer& smartBuffer) {
    std::string test;
    smartBuffer >> test;
    Logger::info("[Protocol] DEFAULT - Test: " + test);
}

void Protocol::handleCreateRoomCallback(SmartBuffer& smartBuffer) {
    int16_t statusCode;
    smartBuffer >> statusCode;
    Logger::info("[Protocol] CREATE_ROOM_CALLBACK - Status Code: " + std::to_string(statusCode));
}

void Protocol::handleCreateRoomBroadcast(SmartBuffer& smartBuffer) {
    std::string roomCode;
    smartBuffer >> roomCode;
    Logger::info("[Protocol] CREATE_ROOM_BROADCAST - Room Code: " + roomCode);
}

void Protocol::handleJoinRoomCallback(SmartBuffer& smartBuffer) {
    int16_t statusCode;
    smartBuffer >> statusCode;
    Logger::info("[Protocol] JOIN_ROOM_CALLBACK - Status Code: " + std::to_string(statusCode));
}

void Protocol::handleJoinRoomBroadcast(SmartBuffer& smartBuffer) {
    std::string roomCode;
    int32_t playerId;
    smartBuffer >> roomCode >> playerId;
    Logger::info("[Protocol] JOIN_ROOM_BROADCAST - Room Code: " + roomCode +
                 ", Player ID: " + std::to_string(playerId));
}

void Protocol::handleDeleteRoomCallback(SmartBuffer& smartBuffer) {
    int16_t statusCode;
    smartBuffer >> statusCode;
    Logger::info("[Protocol] DELETE_ROOM_CALLBACK - Status Code: " + std::to_string(statusCode));
}

void Protocol::handleDeleteRoomBroadcast(SmartBuffer& smartBuffer) {
    std::string roomCode;
    smartBuffer >> roomCode;
    Logger::info("[Protocol] DELETE_ROOM_BROADCAST - Room Code: " + roomCode);
}

void Protocol::handleNewPlayerBroadcast(SmartBuffer& smartBuffer, Client* client) {
    int32_t playerId;
    std::string playerName;
    smartBuffer >> playerId >> playerName;

    Logger::info("[Protocol] NEW_PLAYER_BROADCAST - Player ID: " + std::to_string(playerId) +
                 ", Player Name: " + playerName);

    {
        std::lock_guard<std::mutex> lock(_playerPositionsMutex);

        if (_playerPositions.find(playerId) == _playerPositions.end()) {
            _playerPositions[playerId] = {0.0f, 0.0f};
        }
    }

    std::map<int, std::map<std::string, std::any>> newPlayer = {
        {playerId,
         {{"Texture", "../assets/sprite/tentacles.png"},
          {"Position", std::make_pair(0.0f, 0.0f)}}}};
    client->addItem(newPlayer);
}

void Protocol::handlePlayerUpdatePosition(SmartBuffer& smartBuffer, Client* client) {
    int32_t playerId;
    float x, y;
    smartBuffer >> playerId >> x >> y;

    Logger::info("[Protocol] Updating Player Position - Player ID: " + std::to_string(playerId) +
                 ", New Position: (" + std::to_string(x) + ", " + std::to_string(y) + ").");

    {
        std::lock_guard<std::mutex> lock(_playerPositionsMutex);

        if (_playerPositions.find(playerId) == _playerPositions.end()) {
            Logger::info("[Protocol] Creating new player entry for Player ID: " + std::to_string(playerId));
            _playerPositions[playerId] = {0.0f, 0.0f};

            std::map<int, std::map<std::string, std::any>> newPlayer = {
                {playerId,
                 {{"Texture", "../assets/sprite/tentacles.png"},
                  {"Position", std::make_pair(0.0f, 0.0f)}}}};
            client->addItem(newPlayer);
        }

        _playerPositions[playerId] = {x, y};
    }

    std::map<int, std::map<std::string, std::any>> updatedPlayer = {
        {playerId, {{"Position", std::make_pair(x, y)}}}};
    client->setUpdateItems(updatedPlayer);

    Logger::info("[Protocol] Player position updated successfully for Player ID: " + std::to_string(playerId));
}