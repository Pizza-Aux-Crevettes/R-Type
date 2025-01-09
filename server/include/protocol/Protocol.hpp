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
        PLAYER_UPDATE_POSITION = 13,
        PLAYER_UPDATE_LIFE = 14,

        MAP_VIEWPORT_UPDATE = 20,
        MAP_OBSTACLES_UPDATE = 21,
    };

    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    static Protocol& get();
    static void handleMessage(int clientSocket, SmartBuffer& smartBuffer,
                              const sockaddr_in& clientAddr);

  private:
    Protocol() = default;
    ~Protocol() = default;
};
