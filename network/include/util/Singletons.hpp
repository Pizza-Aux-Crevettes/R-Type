/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Singletons.hpp
*/

#pragma once

#include "component/player/PlayerManager.hpp"
#include "component/room/RoomManager.hpp"
#include "protocol/Protocol.hpp"
#include "socket/Server.hpp"

class Singletons {
  public:
    static Server& getServer();
    static RoomManager& getRoomManager();
    static PlayerManager& getPlayerManager();
    static Protocol& getProtocol();

  private:
    Singletons() = default;
    ~Singletons() = default;
    Singletons(const Singletons&) = delete;
    Singletons& operator=(const Singletons&) = delete;
};
