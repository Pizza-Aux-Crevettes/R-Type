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
        PLAYER_POSITION_UPDATE = 13,
        PLAYER_LIFE_UPDATE = 14,

        MAP_VIEWPORT_UPDATE = 20,
        MAP_OBSTACLES_UPDATE = 21,

        BULLET_POSITION_UPDATE = 30,
    };

    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    static Protocol& get();
    static void handleMessage(SmartBuffer& smartBuffer);
    static int32_t getPlayerId();
    static void setPlayerId(int32_t playerId);

  private:
    Protocol() = default;
    ~Protocol() = default;

    static int32_t _playerId;

    static void handleDefault(SmartBuffer& smartBuffer);
    static void handleNewPlayerCallback(SmartBuffer& smartBuffer);
    static void handleNewPlayerBroadcast(SmartBuffer& smartBuffer);
    static void handlePlayerUpdatePosition(SmartBuffer& smartBuffer);
    static void handlePlayerUpdateLife(SmartBuffer& smartBuffer);
    static void handleViewportUpdate(SmartBuffer& smartBuffer);
    static void handleBlocksUpdate(SmartBuffer& smartBuffer);
    static void handleBulletsUpdate(SmartBuffer& smartBuffer);
};
