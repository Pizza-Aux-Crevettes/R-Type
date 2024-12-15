/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Protocol.hpp
*/

#pragma once

#include <SmartBuffer.hpp>
#include "Client.hpp"
#include <iostream>
#include <map>
#include <string>
#include <utility>

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

    static Protocol& get();
    static void handleMessage(SmartBuffer& smartBuffer, Client *client);
    std::unordered_map<int32_t, std::pair<float, float>> _playerPositions;

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
    static void handleNewPlayerBroadcast(SmartBuffer& smartBuffer, Client *client);
    static void handlePlayerCallback(SmartBuffer& smartBuffer, Client *client);
    static void handlePlayerUpdatePosition(SmartBuffer& smartBuffer, Client *client);
};
