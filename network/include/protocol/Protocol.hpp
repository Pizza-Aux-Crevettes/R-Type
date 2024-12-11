/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Protocol.hpp
*/

#pragma once

#include <SmartBuffer.hpp>

class Protocol {
  public:
    enum OpCode {
        DEFAULT,
        CREATE_ROOM,
        CREATE_ROOM_CALLBACK,
        JOIN_ROOM,
        JOIN_ROOM_CALLBACK,
        DELETE_ROOM,
        DELETE_ROOM_CALLBACK,
        NEW_PLAYER,
        NEW_PLAYER_CALLBACK,
    };

    static Protocol& getInstance();

    void handleMessage(int clientSocket, SmartBuffer& smartBuffer);

  private:
    Protocol();
    ~Protocol();
    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    void createRoom(int clientSocket, SmartBuffer& smartBuffer);
    void joinRoom(int clientSocket, SmartBuffer& smartBuffer);
    void deleteRoom(int clientSocket, SmartBuffer& smartBuffer);
};
