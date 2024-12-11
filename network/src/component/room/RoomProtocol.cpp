/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** RoomProtocol.cpp
*/

/**
 * @file RoomProtocol.cpp
 * @brief Implements room-related operations for the game, such as creating,
 * joining, and deleting rooms.
 */

#include "component/room/RoomProtocol.hpp"
#include "protocol/Protocol.hpp"
#include "socket/TcpSocket.hpp"
#include "util/Logger.hpp"
#include "util/Singletons.hpp"

/**
 * Protocol structure:
 * - Input: int32_t playerId >> int16_t capacity >> int16_t isPublic
 * - Output: int16_t opCode (CREATE_ROOM_CALLBACK) << int16_t status <<
 * std::string roomCode (optional)
 *
 * Status codes:
 * - 0 = Room created
 * - 1 = Player not found
 */
void RoomProtocol::createRoom(int clientSocket, SmartBuffer& smartBuffer) {
    int32_t playerId;
    int16_t capacity;
    int16_t isPublic;

    smartBuffer >> playerId >> capacity >> isPublic;
    smartBuffer.reset();
    smartBuffer << int16_t(Protocol::OpCode::CREATE_ROOM_CALLBACK);

    Logger::trace("[RoomProtocol] Processing CREATE_ROOM. playerId = " +
                  std::to_string(playerId) +
                  ", capacity = " + std::to_string(capacity) +
                  ", isPublic = " + std::to_string(isPublic));

    auto player = Singletons::getPlayerManager().findPlayerById(playerId);

    int16_t status = !player;
    smartBuffer << status;

    std::string roomCode;
    if (!status) {
        roomCode = Singletons::getRoomManager()
                       .createRoom(player, capacity, isPublic)
                       ->getCode();
        smartBuffer << roomCode;
    }

    TcpSocket::send(clientSocket, smartBuffer);

    if (!status) {
        Logger::success("[RoomProtocol] Room created successfully with code: " +
                        roomCode);
    }
}

/**
 * Protocol structure:
 * - Input: std::string roomCode >> int32_t playerId
 * - Output: int16_t opCode (JOIN_ROOM_CALLBACK) << int16_t status
 *
 * Status codes:
 * - 0 = Room joined
 * - 1 = Player not found
 * - 2 = Room not found
 * - 3 = Cannot add player to the room
 */
void RoomProtocol::joinRoom(int clientSocket, SmartBuffer& smartBuffer) {
    std::string roomCode;
    int32_t playerId;

    smartBuffer >> roomCode >> playerId;
    smartBuffer.reset();
    smartBuffer << int16_t(Protocol::OpCode::JOIN_ROOM_CALLBACK);

    Logger::trace("[RoomProtocol] Processing JOIN_ROOM. roomCode = " +
                  roomCode + ", playerId = " + std::to_string(playerId));

    auto player = Singletons::getPlayerManager().findPlayerById(playerId);
    auto room = Singletons::getRoomManager().findRoomByCode(roomCode);

    int16_t status = (!player + !room + (!room->addPlayer(player)));
    smartBuffer << status;

    TcpSocket::send(clientSocket, smartBuffer);

    if (!status) {
        Logger::info("[RoomProtocol] Player " + player->getName() +
                     " joined room: " + roomCode);
    }
}

/**
 * Protocol structure:
 * - Input: std::string roomCode >> int32_t playerId
 * - Output: int16_t opCode (DELETE_ROOM_CALLBACK) << int16_t status
 *
 * Status codes:
 * - 0 = Room deleted
 * - 1 = Player not found
 * - 2 = Room not found
 * - 3 = Permission not granted
 */
void RoomProtocol::deleteRoom(int clientSocket, SmartBuffer& smartBuffer) {
    std::string roomCode;
    int32_t playerId;

    smartBuffer >> roomCode >> playerId;
    smartBuffer.reset();
    smartBuffer << int16_t(Protocol::OpCode::DELETE_ROOM_CALLBACK);

    Logger::trace("[RoomProtocol] Processing DELETE_ROOM. roomCode = " +
                  roomCode + ", playerId = " + std::to_string(playerId));

    auto player = Singletons::getPlayerManager().findPlayerById(playerId);
    auto room = Singletons::getRoomManager().findRoomByCode(roomCode);

    int16_t status = (!player + !room + (room->getOwner() != player));
    smartBuffer << status;

    if (!status) {
        Singletons::getRoomManager().deleteRoom(roomCode, player);
    }

    TcpSocket::send(clientSocket, smartBuffer);

    if (!status) {
        Logger::info("[RoomProtocol] Room deleted successfully. Room code: " +
                     roomCode);
    }
}
