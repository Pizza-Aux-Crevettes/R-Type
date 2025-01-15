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
        CREATE_PLAYER = 10,
        CREATE_PLAYER_CALLBACK = 11,
        CREATE_PLAYER_BROADCAST = 12,
        UPDATE_PLAYERS = 20,
        UPDATE_VIEWPORT = 21,
        UPDATE_OBSTACLES = 22,
        UPDATE_BULLETS = 23,
        UPDATE_ENEMIES = 24,
        DELETE_ENTITY = 30,
    };

    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    static Protocol& get();

    static int32_t getPlayerId();
    static void setPlayerId(int32_t playerId);
    static void handleMessage(SmartBuffer& smartBuffer);

  private:
    Protocol() = default;
    ~Protocol() = default;

    static int32_t _playerId;

    static void handleCreatePlayerCallback(SmartBuffer& smartBuffer);
    static void handleCreatePlayerBroadcast(SmartBuffer& smartBuffer);
    static void handleUpdatePlayer(SmartBuffer& smartBuffer);
    static void handleUpdateViewport(SmartBuffer& smartBuffer);
    static void handleUpdateBlocks(SmartBuffer& smartBuffer);
    static void handleUpdateBullets(SmartBuffer& smartBuffer);
    static void handleUpdateEnemies(SmartBuffer& smartBuffer);
    static void handleDeleteEntity(SmartBuffer& smartBuffer);
};
