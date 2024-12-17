/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** RoomProtocol.cpp
*/

#include "component/room/RoomProtocol.hpp"
#include "component/player/PlayerManager.hpp"
#include "component/room/RoomManager.hpp"
#include "component/map/MapManager.hpp"
#include "protocol/Protocol.hpp"
#include "socket/TcpSocket.hpp"
#include "util/Logger.hpp"

/**
 * Protocol structure:
 * - Input: int32_t userId >> int16_t capacity >> int16_t isPublic >> int16_t mapId
 * - Output: int16_t opCode (CREATE_ROOM_CALLBACK) << int16_t status
 *
 * Status codes:
 * - 0 = Room created
 * - 1 = Player not found
 */
void RoomProtocol::createRoom(const int clientSocket,
                              SmartBuffer& smartBuffer) {
    int32_t userId;
    int16_t capacity;
    int16_t isPublic;
    int16_t mapId;

    smartBuffer >> userId >> capacity >> isPublic >> mapId;
    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::CREATE_ROOM_CALLBACK);

    Logger::trace("[RoomProtocol] Processing CREATE_ROOM. userId = " +
                  std::to_string(userId) +
                  ", capacity = " + std::to_string(capacity) +
                  ", isPublic = " + std::to_string(isPublic) +
                  ", mapId = " + std::to_string(mapId));

    const auto player = PlayerManager::get().findPlayerById(userId);
    const auto status = static_cast<int16_t>(!player);

    smartBuffer << status;

    if (!status) {
        auto room = RoomManager::get().createRoom(player, capacity, isPublic);
        auto selectedMap = MapManager::get().loadMap(mapId);
        room->setMap(selectedMap);

        Logger::success("[RoomProtocol] Room created with code: " +
                        room->getCode() + ", Map ID: " + std::to_string(mapId));
    }

    TcpSocket::sendToOne(clientSocket, smartBuffer);
}

/**
 * Protocol structure:
 * - Input: std::string roomCode >> int32_t userId
 * - Output: int16_t opCode (JOIN_ROOM_CALLBACK) << int16_t status
 *
 * Status codes:
 * - 0 = Room joined
 * - 1 = Player not found
 * - 2 = Room not found
 * - 3 = Cannot add player to the room
 */
void RoomProtocol::joinRoom(const int clientSocket, SmartBuffer& smartBuffer) {
    std::string roomCode;
    int32_t userId;

    smartBuffer >> roomCode >> userId;
    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::JOIN_ROOM_CALLBACK);

    Logger::trace("[RoomProtocol] Processing JOIN_ROOM. roomCode = " +
                  roomCode + ", userId = " + std::to_string(userId));

    const auto player = PlayerManager::get().findPlayerById(userId);
    const auto room = RoomManager::get().findRoomByCode(roomCode);
    const auto status =
        static_cast<int16_t>(!player + !room + !room->addPlayer(player));

    smartBuffer << status;

    if (!status) {
        Logger::info("[RoomProtocol] Player " + player->getName() +
                     " joined room: " + roomCode);
    }

    TcpSocket::sendToOne(clientSocket, smartBuffer);
}

/**
 * Protocol structure:
 * - Input: std::string roomCode >> int32_t userId
 * - Output: P
 *
 * Status codes:
 * - 0 = Room deleted
 * - 1 = Player not found
 * - 2 = Room not found
 * - 3 = Permission not granted
 */
void RoomProtocol::deleteRoom(const int clientSocket,
                              SmartBuffer& smartBuffer) {
    std::string roomCode;
    int32_t userId;

    smartBuffer >> roomCode >> userId;
    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::DELETE_ROOM_CALLBACK);

    Logger::trace("[RoomProtocol] Processing DELETE_ROOM. roomCode = " +
                  roomCode + ", userId = " + std::to_string(userId));

    const auto player = PlayerManager::get().findPlayerById(userId);
    const auto room = RoomManager::get().findRoomByCode(roomCode);
    const auto status =
        static_cast<int16_t>(!player + !room + (room->getOwner() != player));

    smartBuffer << status;

    if (!status) {
        RoomManager::get().deleteRoom(roomCode, player);

        Logger::info("[RoomProtocol] Room deleted successfully. Room code: " +
                     roomCode);
    }

    TcpSocket::sendToOne(clientSocket, smartBuffer);
}
