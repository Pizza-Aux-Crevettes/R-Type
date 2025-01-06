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
        
        // Client -> Server
        CREATE_ROOM,
        JOIN_ROOM,
        DELETE_ROOM,
        NEW_PLAYER,
        HOTKEY_PRESSED,

        // Server -> Client
        CREATE_ROOM_CALLBACK,
        JOIN_ROOM_CALLBACK,
        DELETE_ROOM_CALLBACK,
        NEW_PLAYER_CALLBACK,

        // Server -> All clients
        CREATE_ROOM_BROADCAST,
        JOIN_ROOM_BROADCAST,
        DELETE_ROOM_BROADCAST,
        NEW_PLAYER_BROADCAST,
        PLAYER_UPDATE_POSITION,
        PLAYER_UPDATE_LIFE,
        VIEWPORT_UPDATE,
        BLOCKS_UPDATE,
    };

    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    static Protocol& get();
    static void handleMessage(SmartBuffer& smartBuffer, Client* client);

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
    static void handleNewPlayerBroadcast(SmartBuffer& smartBuffer,
                                         Client* client);
    static void handlePlayerCallback(SmartBuffer& smartBuffer, Client* client);
    static void handlePlayerUpdatePosition(SmartBuffer& smartBuffer,
                                           Client* client);
};
