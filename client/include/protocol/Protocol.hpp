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

    static Protocol& getInstance();

    void handleMessage(SmartBuffer& smartBuffer);

  private:
    Protocol();
    ~Protocol();
    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    void handleDefault(SmartBuffer& smartBuffer);
    void handleCreateRoomCallback(SmartBuffer& smartBuffer);
    void handleCreateRoomBroadcast(SmartBuffer& smartBuffer);
    void handleJoinRoomCallback(SmartBuffer& smartBuffer);
    void handleJoinRoomBroadcast(SmartBuffer& smartBuffer);
    void handleDeleteRoomCallback(SmartBuffer& smartBuffer);
    void handleDeleteRoomBroadcast(SmartBuffer& smartBuffer);
    void handleNewPlayerBroadcast(SmartBuffer& smartBuffer);
    void handlePlayerUpdatePosition(SmartBuffer& smartBuffer);
};
