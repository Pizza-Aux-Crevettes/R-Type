/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Protocol.hpp
*/

#pragma once

#include "Room.hpp"
#include "SmartBuffer.hpp"
#include <memory>
#include <unordered_map>

class Protocol {
  public:
    enum OpCode {
        DEFAULT = 0,
        CREATE_ROOM = 1,
        ROOM_INFO = 2,
        JOIN_ROOM = 3,
        DELETE_ROOM = 4
    };

    Protocol();

    void handleMessage(int clientSocket, SmartBuffer& smartBuffer);

  private:
    void createRoom(int clientSocket, SmartBuffer& smartBuffer);
    void joinRoom(int clientSocket, SmartBuffer& smartBuffer);
    void deleteRoom(int clientSocket, SmartBuffer& smartBuffer);
    void sendRoomInfo(int clientSocket, int32_t roomCode);

    std::unordered_map<int32_t, std::shared_ptr<Room>> rooms;
    std::mutex roomMutex;
};
