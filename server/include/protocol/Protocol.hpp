/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Protocol.hpp
*/

#pragma once

#include <SmartBuffer.hpp>
#include <memory>
#include <netinet/in.h>

class Protocol {
  public:
    enum OpCode {
        DEFAULT = 0,

        HOTKEY_PRESSED = 1,

        NEW_PLAYER = 10,
        NEW_PLAYER_CALLBACK = 11,
        NEW_PLAYER_BROADCAST = 12,
        PLAYERS_UPDATE = 13,
        PLAYER_DELETED = 15,

        VIEWPORT_UPDATE = 20,

        OBSTACLES_UPDATE = 30,
        OBSTACLE_DELETED = 31,

        BULLETS_UPDATE = 40,
        BULLET_DELETED = 41,
    };

    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    static Protocol& get();
    static void handleMessage(int clientSocket, SmartBuffer& smartBuffer);

  private:
    Protocol() = default;
    ~Protocol() = default;
};
