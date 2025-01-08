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
    int32_t userId;
    int16_t capacity;
    int16_t isPublic;
    int16_t mapId;

    smartBuffer >> userId >> capacity >> isPublic >> mapId;
    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::CREATE_ROOM_CALLBACK);

    Logger::trace(
        "[RoomProtocol] CREATE_ROOM: userId=" + std::to_string(userId) +
        ", capacity=" + std::to_string(capacity) + ", isPublic=" +
        std::to_string(isPublic) + ", mapId=" + std::to_string(mapId));

    auto player = PlayerManager::get().findPlayerById(userId);
    int16_t status = player ? 0 : 1;

    smartBuffer << status;

    if (!status) {
        auto room = RoomManager::get().createRoom(player, capacity, isPublic);

        room->setMap(MapManager::get().getMapById(mapId));

        Logger::success("[RoomProtocol] Room created: code=" + room->getCode() +
                        ", mapId=" + std::to_string(mapId));
    }

    TcpSocket::sendToOne(client->getTcpSocket(), smartBuffer);
}

void RoomProtocol::joinRoom(std::shared_ptr<Client> client,
                            SmartBuffer& smartBuffer) {
    std::string roomCode;
    int32_t userId;

    smartBuffer >> roomCode >> userId;
    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::JOIN_ROOM_CALLBACK);

    Logger::trace("[RoomProtocol] JOIN_ROOM: roomCode=" + roomCode +
                  ", userId=" + std::to_string(userId));

    auto player = PlayerManager::get().findPlayerById(userId);
    auto room = RoomManager::get().findRoomByCode(roomCode);
    int16_t status = 0;

    if (!player) {
        status = 1;
    } else if (!room) {
        status = 2;
    } else if (!room->addPlayer(player)) {
        status = 3;
    }

    smartBuffer << status;

    if (!status) {
        Logger::info("[RoomProtocol] Player " + player->getName() +
                     " joined room: " + roomCode);
    }

    TcpSocket::sendToOne(client->getTcpSocket(), smartBuffer);
}

void RoomProtocol::deleteRoom(std::shared_ptr<Client> client,
                              SmartBuffer& smartBuffer) {
    std::string roomCode;
    int32_t userId;

    smartBuffer >> roomCode >> userId;
    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::DELETE_ROOM_CALLBACK);

    Logger::trace("[RoomProtocol] DELETE_ROOM: roomCode=" + roomCode +
                  ", userId=" + std::to_string(userId));

    auto player = PlayerManager::get().findPlayerById(userId);
    auto room = RoomManager::get().findRoomByCode(roomCode);
    int16_t status = 0;

    if (!player) {
        status = 1;
    } else if (!room) {
        status = 2;
    } else if (room->getOwner() != player) {
        status = 3;
    }

    smartBuffer << status;

    if (!status) {
        RoomManager::get().deleteRoom(roomCode, player);
        Logger::info("[RoomProtocol] Room deleted: " + roomCode);
    }

    TcpSocket::sendToOne(client->getTcpSocket(), smartBuffer);
}

void RoomProtocol::startGame(std::shared_ptr<Client> client,
                             SmartBuffer& smartBuffer) {
    std::string roomCode;
    int32_t userId;

    smartBuffer >> roomCode >> userId;
    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::START_GAME_CALLBACK);

    Logger::trace("[RoomProtocol] START_GAME: roomCode=" + roomCode +
                  ", userId=" + std::to_string(userId));

    auto player = PlayerManager::get().findPlayerById(userId);
    auto room = RoomManager::get().findRoomByCode(roomCode);
    int16_t status = 0;

    if (!player) {
        status = 1;
    } else if (!room) {
        status = 2;
    } else if (room->getOwner() != player) {
        status = 3;
    }

    smartBuffer << status;

    if (!status) {
        room->startGame();
        Logger::info("[RoomProtocol] Game started: " + roomCode);
    }

    TcpSocket::sendToOne(client->getTcpSocket(), smartBuffer);
}

void RoomProtocol::stopGame(std::shared_ptr<Client> client,
                            SmartBuffer& smartBuffer) {
    std::string roomCode;
    int32_t userId;

    smartBuffer >> roomCode >> userId;
    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::STOP_GAME_CALLBACK);

    Logger::trace("[RoomProtocol] STOP_GAME: roomCode=" + roomCode +
                  ", userId=" + std::to_string(userId));

    auto player = PlayerManager::get().findPlayerById(userId);
    auto room = RoomManager::get().findRoomByCode(roomCode);
    int16_t status = 0;

    if (!player) {
        status = 1;
    } else if (!room) {
        status = 2;
    } else if (room->getOwner() != player) {
        status = 3;
    }

    smartBuffer << status;

    if (!status) {
        room->stopGame();
        Logger::info("[RoomProtocol] Game stopped: " + roomCode);
    }

    TcpSocket::sendToOne(client->getTcpSocket(), smartBuffer);
}
