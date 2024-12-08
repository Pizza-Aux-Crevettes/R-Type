/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** RoomProtocol.cpp
*/

#include "component/room/RoomProtocol.hpp"
#include "protocol/Protocol.hpp"
#include "socket/TcpSocket.hpp"
#include "util/Logger.hpp"
#include "util/Singletons.hpp"

enum CALLBACKS {
    ROOM_CREATED,
    ROOM_JOINED,
    ROOM_DELETED,
    PLAYER_NOT_FOUND,
    ROOM_NOT_FOUND,
    PERMISSION_DENIED,
    ROOM_FULL,
};

void RoomProtocol::createRoom(int clientSocket, SmartBuffer& smartBuffer) {
    /*
     * Protocol CREATE_ROOM
     * int32_t playerId
     * int8_t capacity
     * bool isPublic
     * Data sent in response: CREATE_ROOM_CALLBACK
     */

    int32_t playerId;
    int8_t capacity;
    bool isPublic;

    smartBuffer >> playerId >> capacity >> isPublic;
    smartBuffer.reset();
    smartBuffer << Protocol::OpCode::CREATE_ROOM_CALLBACK;

    Logger::trace("[RoomProtocol] Processing CREATE_ROOM. playerId = " +
                  std::to_string(playerId) +
                  ", capacity = " + std::to_string(capacity) +
                  ", isPublic = " + (isPublic ? "true" : "false"));

    auto player = Singletons::getPlayerManager().findPlayerById(playerId);

    if (!player) {
        smartBuffer << PLAYER_NOT_FOUND;
        send(clientSocket, smartBuffer.getBuffer(), smartBuffer.getSize(), 0);
        return;
    }

    auto room =
        Singletons::getRoomManager().createRoom(player, capacity, isPublic);

    smartBuffer << ROOM_CREATED << room->getCode();
    TcpSocket::sendTcp(clientSocket, smartBuffer);

    Logger::success("[RoomProtocol] Room created successfully with code: " +
                    room->getCode());
}

void RoomProtocol::joinRoom(int clientSocket, SmartBuffer& smartBuffer) {
    /*
     * Protocol JOIN_ROOM:
     * string roomCode
     * int32_t playerId
     * Data sent in response: JOIN_ROOM_CALLBACK
     */

    std::string roomCode;
    int32_t playerId;

    smartBuffer >> roomCode >> playerId;
    smartBuffer.reset();
    smartBuffer << Protocol::OpCode::JOIN_ROOM_CALLBACK;

    Logger::trace("[RoomProtocol] Processing JOIN_ROOM. roomCode = " +
                  roomCode + ", playerId = " + std::to_string(playerId));

    auto player = Singletons::getPlayerManager().findPlayerById(playerId);
    auto room = Singletons::getRoomManager().findRoomByCode(roomCode);

    if (!player) {
        smartBuffer << PLAYER_NOT_FOUND;
    } else if (!room) {
        smartBuffer << ROOM_NOT_FOUND;
    } else if (!room->addPlayer(player)) {
        smartBuffer << ROOM_FULL;
    } else {
        smartBuffer << ROOM_JOINED;
    }

    TcpSocket::sendTcp(clientSocket, smartBuffer);

    Logger::info("[RoomProtocol] Player " + player->getName() +
                 " joined room: " + roomCode);
}

void RoomProtocol::deleteRoom(int clientSocket, SmartBuffer& smartBuffer) {
    /*
     * Protocol DELETE_ROOM:
     * string roomCode
     * int32_t playerId
     * Data sent in response: DELETE_ROOM_CALLBACK
     */

    std::string roomCode;
    int32_t playerId;

    smartBuffer >> roomCode >> playerId;
    smartBuffer.reset();
    smartBuffer << Protocol::OpCode::DELETE_ROOM_CALLBACK;

    Logger::trace("[RoomProtocol] Processing DELETE_ROOM. roomCode = " +
                  roomCode + ", playerId = " + std::to_string(playerId));

    auto player = Singletons::getPlayerManager().findPlayerById(playerId);
    auto room = Singletons::getRoomManager().findRoomByCode(roomCode);

    if (!player) {
        smartBuffer << PLAYER_NOT_FOUND;
    } else if (!room) {
        smartBuffer << ROOM_NOT_FOUND;
    } else if (room->getOwner() != player) {
        smartBuffer << PERMISSION_DENIED;
    } else {
        Singletons::getRoomManager().deleteRoom(roomCode, player);
        smartBuffer << ROOM_DELETED;
    }

    TcpSocket::sendTcp(clientSocket, smartBuffer);

    Logger::info("[RoomProtocol] Room deleted successfully. Room code: " +
                 roomCode);
}
