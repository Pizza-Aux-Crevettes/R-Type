/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Protocol.hpp
*/

#pragma once

#include <SmartBuffer.hpp>
#include "Client.hpp"

class Protocol {
  public:
    enum OpCode {
        DEFAULT,
        CREATE_ROOM,
        JOIN_ROOM,
        LEAVE_ROOM,
        DELETE_ROOM,
        NEW_PLAYER,
        HOTKEY_PRESSED,
        START_GAME,
        STOP_GAME,

        CREATE_ROOM_CALLBACK,
        LEAVE_ROOM_CALLBACK,
        JOIN_ROOM_CALLBACK,
        DELETE_ROOM_CALLBACK,
        NEW_PLAYER_CALLBACK,
        START_GAME_CALLBACK,
        STOP_GAME_CALLBACK,

        CREATE_ROOM_BROADCAST,
        LEAEVE_ROOM_BROADCAST,
        JOIN_ROOM_BROADCAST,
        DELETE_ROOM_BROADCAST,
        NEW_PLAYER_BROADCAST,
        START_GAME_BROADCAST,
        STOP_GAME_BROADCAST,

        PLAYER_UPDATE_POSITION,
        PLAYER_UPDATE_LIFE,
        VIEWPORT_UPDATE,
        BLOCKS_UPDATE,
    };

    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    static Protocol& get();
    static void handleMessage(SmartBuffer& smartBuffer);

  private:
    Protocol();
    ~Protocol();

    static void handleDefault(SmartBuffer& smartBuffer);
    static void handleCreateRoomCallback(SmartBuffer& smartBuffer);
    static void handleCreateRoomBroadcast(SmartBuffer& smartBuffer);
    static void handleJoinRoomCallback(SmartBuffer& smartBuffer);
    static void handleJoinRoomBroadcast(SmartBuffer& smartBuffer);
    static void handleDeleteRoomCallback(SmartBuffer& smartBuffer);
    static void handleDeleteRoomBroadcast(SmartBuffer& smartBuffer);
    static void handleNewPlayerBroadcast(SmartBuffer& smartBuffer);
    static void handlePlayerCallback(SmartBuffer& smartBuffer);
    static void handlePlayerUpdatePosition(SmartBuffer& smartBuffer);
};
