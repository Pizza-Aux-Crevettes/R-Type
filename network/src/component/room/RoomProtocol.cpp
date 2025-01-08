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
    auto player = client->getPlayer();
    if (!player) {
        Logger::warning(
            "[HotkeysProtocol] No player associated with this client.");
        return;
    }

    int32_t playerId = player->getId();
    int16_t capacity;
    int16_t isPublic;
    int16_t mapId;
    smartBuffer >> capacity >> isPublic >> mapId;

    Logger::trace(
        "[RoomProtocol] CREATE_ROOM: playerId=" + std::to_string(playerId) +
        ", capacity=" + std::to_string(capacity) + ", isPublic=" +
        std::to_string(isPublic) + ", mapId=" + std::to_string(mapId));

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::CREATE_ROOM_CALLBACK);

    int16_t status = player ? 0 : 1;

    smartBuffer << status;

    if (!status) {
        auto room = RoomManager::get().createRoom(player, capacity, isPublic);
        room->setMap(MapManager::get().getMapById(mapId));

        smartBuffer << std::string({room->getCode()});

        Logger::success("[RoomProtocol] Room created: code=" + room->getCode() +
                        ", mapId=" + std::to_string(mapId));
    }

    TcpSocket::sendToOne(client->getTcpSocket(), smartBuffer);
}

void RoomProtocol::joinRoom(std::shared_ptr<Client> client,
                            SmartBuffer& smartBuffer) {
    auto player = client->getPlayer();
    if (!player) {
        Logger::warning(
            "[HotkeysProtocol] No player associated with this client.");
        return;
    }

    int32_t playerId = player->getId();
    std::string roomCode;
    smartBuffer >> roomCode;

    Logger::trace("[RoomProtocol] JOIN_ROOM: roomCode=" + roomCode +
                  ", playerId=" + std::to_string(playerId));

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::JOIN_ROOM_CALLBACK);

    auto room = RoomManager::get().findRoomByCode(roomCode);
    int16_t status = 0;

    if (!room) {
        status = 1;
    } else if (!room->addPlayer(player)) {
        status = 2;
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
    auto player = client->getPlayer();
    if (!player) {
        Logger::warning(
            "[HotkeysProtocol] No player associated with this client.");
        return;
    }

    int32_t playerId = player->getId();
    std::string roomCode;
    smartBuffer >> roomCode;

    Logger::trace("[RoomProtocol] DELETE_ROOM: roomCode=" + roomCode +
                  ", playerId=" + std::to_string(playerId));

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::DELETE_ROOM_CALLBACK);

    auto room = RoomManager::get().findRoomByCode(roomCode);
    int16_t status = 0;

    if (!room) {
        status = 1;
    } else if (room->getOwner() != player) {
        status = 2;
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
    auto player = client->getPlayer();
    if (!player) {
        Logger::warning(
            "[HotkeysProtocol] No player associated with this client.");
        return;
    }

    int32_t playerId = player->getId();
    std::string roomCode;
    smartBuffer >> roomCode;

    Logger::trace("[RoomProtocol] START_GAME: roomCode=" + roomCode +
                  ", playerId=" + std::to_string(playerId));

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::START_GAME_CALLBACK);

    auto room = RoomManager::get().findRoomByCode(roomCode);
    int16_t status = 0;

    if (!room) {
        status = 1;
    } else if (room->getOwner() != player) {
        status = 2;
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
    auto player = client->getPlayer();
    if (!player) {
        Logger::warning(
            "[HotkeysProtocol] No player associated with this client.");
        return;
    }

    int32_t playerId = player->getId();
    std::string roomCode;
    smartBuffer >> roomCode;

    Logger::trace("[RoomProtocol] STOP_GAME: roomCode=" + roomCode +
                  ", playerId=" + std::to_string(playerId));

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::STOP_GAME_CALLBACK);

    auto room = RoomManager::get().findRoomByCode(roomCode);
    int16_t status = 0;

    if (!room) {
        status = 1;
    } else if (room->getOwner() != player) {
        status = 2;
    }

    smartBuffer << status;

    if (!status) {
        room->stopGame();

        Logger::info("[RoomProtocol] Game stopped: " + roomCode);
    }

    TcpSocket::sendToOne(client->getTcpSocket(), smartBuffer);
}
