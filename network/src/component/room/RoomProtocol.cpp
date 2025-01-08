/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** RoomProtocol.cpp
*/

#include "component/room/RoomProtocol.hpp"
#include "component/map/MapManager.hpp"
#include "component/player/PlayerManager.hpp"
#include "component/room/RoomManager.hpp"
#include "protocol/Protocol.hpp"
#include "socket/TcpSocket.hpp"
#include "util/Logger.hpp"

void RoomProtocol::createRoom(std::shared_ptr<Client> client,
                              SmartBuffer& smartBuffer) {
    Logger::info("[RoomProtocol] Handling CREATE_ROOM request.");

    auto player = client->getPlayer();
    if (!player) {
        Logger::warning(
            "[RoomProtocol] No player associated with this client.");
        return;
    }

    int32_t playerId = player->getId();
    int16_t capacity;
    int16_t isPublic;
    int16_t mapId;

    smartBuffer >> capacity >> isPublic >> mapId;

    Logger::trace("[RoomProtocol] CREATE_ROOM details: playerId=" +
                  std::to_string(playerId) +
                  ", capacity=" + std::to_string(capacity) +
                  ", isPublic=" + std::to_string(isPublic) +
                  ", mapId=" + std::to_string(mapId));

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::CREATE_ROOM_CALLBACK);

    int16_t status = 0;
    try {
        auto room = RoomManager::get().createRoom(player, capacity, isPublic);
        room->setMap(MapManager::get().getMapById(mapId));

        smartBuffer << status << room->getCode();

        Logger::success("[RoomProtocol] Room successfully created. Code: " +
                        room->getCode() + ", Map ID: " + std::to_string(mapId));
    } catch (const std::exception& e) {
        status = 1;
        smartBuffer << status;
        Logger::error("[RoomProtocol] Failed to create room: " +
                      std::string(e.what()));
    }

    TcpSocket::sendToOne(client->getTcpSocket(), smartBuffer);
}

void RoomProtocol::joinRoom(std::shared_ptr<Client> client,
                            SmartBuffer& smartBuffer) {
    Logger::info("[RoomProtocol] Handling JOIN_ROOM request.");

    auto player = client->getPlayer();
    if (!player) {
        Logger::warning(
            "[RoomProtocol] No player associated with this client.");
        return;
    }

    int32_t playerId = player->getId();
    std::string roomCode;

    smartBuffer >> roomCode;

    Logger::trace("[RoomProtocol] JOIN_ROOM details: roomCode=" + roomCode +
                  ", playerId=" + std::to_string(playerId));

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::JOIN_ROOM_CALLBACK);

    auto room = RoomManager::get().findRoomByCode(roomCode);
    int16_t status = 0;

    if (!room) {
        status = 1;
        Logger::warning("[RoomProtocol] Room with code " + roomCode +
                        " not found.");
    } else if (!room->addPlayer(player)) {
        status = 2;
        Logger::warning("[RoomProtocol] Failed to add player " +
                        player->getName() + " to room " + roomCode);
    } else {
        Logger::info("[RoomProtocol] Player " + player->getName() +
                     " successfully joined room: " + roomCode);
    }

    smartBuffer << status;
    TcpSocket::sendToOne(client->getTcpSocket(), smartBuffer);
}

void RoomProtocol::deleteRoom(std::shared_ptr<Client> client,
                              SmartBuffer& smartBuffer) {
    Logger::info("[RoomProtocol] Handling DELETE_ROOM request.");

    auto player = client->getPlayer();
    if (!player) {
        Logger::warning(
            "[RoomProtocol] No player associated with this client.");
        return;
    }

    int32_t playerId = player->getId();
    std::string roomCode;

    smartBuffer >> roomCode;

    Logger::trace("[RoomProtocol] DELETE_ROOM details: roomCode=" + roomCode +
                  ", playerId=" + std::to_string(playerId));

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::DELETE_ROOM_CALLBACK);

    auto room = RoomManager::get().findRoomByCode(roomCode);
    int16_t status = 0;

    if (!room) {
        status = 1;
        Logger::warning("[RoomProtocol] Room with code " + roomCode +
                        " not found.");
    } else if (room->getOwner() != player) {
        status = 2;
        Logger::warning("[RoomProtocol] Player " + player->getName() +
                        " is not the owner of room " + roomCode);
    } else {
        RoomManager::get().deleteRoom(roomCode, player);
        Logger::info("[RoomProtocol] Room deleted successfully: " + roomCode);
    }

    smartBuffer << status;
    TcpSocket::sendToOne(client->getTcpSocket(), smartBuffer);
}

void RoomProtocol::startGame(std::shared_ptr<Client> client,
                             SmartBuffer& smartBuffer) {
    Logger::info("[RoomProtocol] Handling START_GAME request.");

    auto player = client->getPlayer();
    if (!player) {
        Logger::warning(
            "[RoomProtocol] No player associated with this client.");
        return;
    }

    int32_t playerId = player->getId();
    std::string roomCode;

    smartBuffer >> roomCode;

    Logger::trace("[RoomProtocol] START_GAME details: roomCode=" + roomCode +
                  ", playerId=" + std::to_string(playerId));

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::START_GAME_CALLBACK);

    auto room = RoomManager::get().findRoomByCode(roomCode);
    int16_t status = 0;

    if (!room) {
        status = 1;
        Logger::warning("[RoomProtocol] Room with code " + roomCode +
                        " not found.");
    } else if (room->getOwner() != player) {
        status = 2;
        Logger::warning("[RoomProtocol] Player " + player->getName() +
                        " is not the owner of room " + roomCode);
    } else {
        room->startGame();
        Logger::info("[RoomProtocol] Game started successfully in room: " +
                     roomCode);
    }

    smartBuffer << status;
    TcpSocket::sendToOne(client->getTcpSocket(), smartBuffer);
}

void RoomProtocol::stopGame(std::shared_ptr<Client> client,
                            SmartBuffer& smartBuffer) {
    Logger::info("[RoomProtocol] Handling STOP_GAME request.");

    auto player = client->getPlayer();
    if (!player) {
        Logger::warning(
            "[RoomProtocol] No player associated with this client.");
        return;
    }

    int32_t playerId = player->getId();
    std::string roomCode;

    smartBuffer >> roomCode;

    Logger::trace("[RoomProtocol] STOP_GAME details: roomCode=" + roomCode +
                  ", playerId=" + std::to_string(playerId));

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::STOP_GAME_CALLBACK);

    auto room = RoomManager::get().findRoomByCode(roomCode);
    int16_t status = 0;

    if (!room) {
        status = 1;
        Logger::warning("[RoomProtocol] Room with code " + roomCode +
                        " not found.");
    } else if (room->getOwner() != player) {
        status = 2;
        Logger::warning("[RoomProtocol] Player " + player->getName() +
                        " is not the owner of room " + roomCode);
    } else {
        room->stopGame();
        Logger::info("[RoomProtocol] Game stopped successfully in room: " +
                     roomCode);
    }

    smartBuffer << status;
    TcpSocket::sendToOne(client->getTcpSocket(), smartBuffer);
}