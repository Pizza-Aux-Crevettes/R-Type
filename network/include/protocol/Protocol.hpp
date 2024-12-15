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
        CREATE_ROOM_BROADCAST,
        JOIN_ROOM,
        JOIN_ROOM_CALLBACK,
        JOIN_ROOM_BROADCAST,
        DELETE_ROOM,
        DELETE_ROOM_CALLBACK,
        DELETE_ROOM_BROADCAST,
        NEW_PLAYER,
        NEW_PLAYER_CALLBACK,
        NEW_PLAYER_BROADCAST,
        PLAYER_UPDATE_POSITION,
        HOTKEY_PRESSED
    };

    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    static Protocol& getInstance();
    static void handleMessage(int clientSocket, SmartBuffer& smartBuffer);

  private:
    Protocol();
    ~Protocol() = default;
};
