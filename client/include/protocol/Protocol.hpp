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
        DEFAULT = 0,

        HOTKEY_PRESSED = 1,

        NEW_PLAYER = 10,
        NEW_PLAYER_CALLBACK = 11,
        NEW_PLAYER_BROADCAST = 12,
        PLAYER_UPDATE_POSITION = 13,
        PLAYER_UPDATE_LIFE = 14,

        MAP_VIEWPORT_UPDATE = 20,
        MAP_OBSTACLES_UPDATE = 21,
    };

    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    static Protocol& get();
    static void handleMessage(SmartBuffer& smartBuffer);

    static int32_t getPlayerId();
    static void setPlayerId(int32_t playerId);

  private:
    Protocol();
    ~Protocol();

    static int32_t _playerId;

    static void handleDefault(SmartBuffer& smartBuffer);

    static void handleCreateRoomCallback(SmartBuffer& smartBuffer);
    static void handleLeaveRoomCallback(SmartBuffer& smartBuffer);
    static void handleJoinRoomCallback(SmartBuffer& smartBuffer);
    static void handleDeleteRoomCallback(SmartBuffer& smartBuffer);
    static void handleNewPlayerCallback(SmartBuffer& smartBuffer);
    static void handleStartGameCallback(SmartBuffer& smartBuffer);
    static void handleStopGameCallback(SmartBuffer& smartBuffer);

    static void handleCreateRoomBroadcast(SmartBuffer& smartBuffer);
    static void handleLeaveRoomBroadcast(SmartBuffer& smartBuffer);
    static void handleJoinRoomBroadcast(SmartBuffer& smartBuffer);
    static void handleDeleteRoomBroadcast(SmartBuffer& smartBuffer);
    static void handleNewPlayerBroadcast(SmartBuffer& smartBuffer);
    static void handleStartGameBroadcast(SmartBuffer& smartBuffer);
    static void handleStopGameBroadcast(SmartBuffer& smartBuffer);

    static void handlePlayerUpdatePosition(SmartBuffer& smartBuffer);
    static void handlePlayerUpdateLife(SmartBuffer& smartBuffer);
    static void handleViewportUpdate(SmartBuffer& smartBuffer);
    static void handleBlocksUpdate(SmartBuffer& smartBuffer);
};
