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

void RoomProtocol::createRoom(int clientSocket, SmartBuffer& smartBuffer) {
    // Protocol structure
    int32_t playerId;
    int8_t capacity;
    int8_t isPublic;

    // Get the data from SmartBuffer after injection
    smartBuffer >> playerId >> capacity >> isPublic;

    // Reset and init for response
    smartBuffer.reset();
    smartBuffer << int8_t(Protocol::OpCode::CREATE_ROOM_CALLBACK);

    Logger::trace("[RoomProtocol] Processing CREATE_ROOM. playerId = " +
                  std::to_string(playerId) +
                  ", capacity = " + std::to_string(capacity) +
                  ", isPublic = " + (isPublic ? "true" : "false"));

    // Check relevant data
    auto player = Singletons::getPlayerManager().findPlayerById(playerId);

    /*
     * Status:
     * 0 = Room created
     * 1 = Player not found
     */
    int8_t status = !player;
    smartBuffer << status;

    // Inject room's code if the status authorize it
    std::string roomCode = "";
    if (!status) {
        roomCode = Singletons::getRoomManager()
                       .createRoom(player, capacity, isPublic)
                       ->getCode();
        smartBuffer << roomCode;
    }

    // Send back the data to client
    TcpSocket::sendTcp(clientSocket, smartBuffer);

    // Log if success
    if (!status) {
        Logger::success("[RoomProtocol] Room created successfully with code: " +
                        roomCode);
    }
}

void RoomProtocol::joinRoom(int clientSocket, SmartBuffer& smartBuffer) {
    // Protocol structure
    std::string roomCode;
    int32_t playerId;

    // Get the data from SmartBuffer after injection
    smartBuffer >> roomCode >> playerId;

    // Reset and init for response
    smartBuffer.reset();
    smartBuffer << Protocol::OpCode::JOIN_ROOM_CALLBACK;

    Logger::trace("[RoomProtocol] Processing JOIN_ROOM. roomCode = " +
                  roomCode + ", playerId = " + std::to_string(playerId));

    // Get relevant data
    auto player = Singletons::getPlayerManager().findPlayerById(playerId);
    auto room = Singletons::getRoomManager().findRoomByCode(roomCode);

    /*
     * Status:
     * 0 = Room joined
     * 1 = Player not found
     * 2 = Room not found
     * 3 = Can't add player to the room
     */
    int8_t status = (!player + !room + (!room->addPlayer(player)));
    smartBuffer << status;

    // Send back the data to client
    TcpSocket::sendTcp(clientSocket, smartBuffer);

    // Log if success
    if (!status) {
        Logger::info("[RoomProtocol] Player " + player->getName() +
                     " joined room: " + roomCode);
    }
}

void RoomProtocol::deleteRoom(int clientSocket, SmartBuffer& smartBuffer) {
    // Protocol structure
    std::string roomCode;
    int32_t playerId;

    // Get the data from SmartBuffer after injection
    smartBuffer >> roomCode >> playerId;

    // Reset and init for response
    smartBuffer.reset();
    smartBuffer << Protocol::OpCode::DELETE_ROOM_CALLBACK;

    Logger::trace("[RoomProtocol] Processing DELETE_ROOM. roomCode = " +
                  roomCode + ", playerId = " + std::to_string(playerId));

    // Check relevant data
    auto player = Singletons::getPlayerManager().findPlayerById(playerId);
    auto room = Singletons::getRoomManager().findRoomByCode(roomCode);

    /*
     * Status:
     * 0 = Room deleted
     * 1 = Player not found
     * 2 = Room not found
     * 3 = Permission not granted
     */
    int8_t status = (!player + !room + (room->getOwner() != player));
    smartBuffer << int8_t(status);

    // Delete room if the status authorize it
    if (!status) {
        Singletons::getRoomManager().deleteRoom(roomCode, player);
    }

    // Send back the data to client
    TcpSocket::sendTcp(clientSocket, smartBuffer);

    // Log if success
    if (!status) {
        Logger::info("[RoomProtocol] Room deleted successfully. Room code: " +
                     roomCode);
    }
}
