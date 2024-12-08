/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Singletons.hpp
*/

#pragma once

#include "component/room/RoomManager.hpp"
#include "protocol/Protocol.hpp"

class Singletons {
  public:
    static RoomManager& getRoomManager();
    static Protocol& getProtocol();

  private:
    Singletons() = default;
    ~Singletons() = default;
    Singletons(const Singletons&) = delete;

    Singletons& operator=(const Singletons&) = delete;
};
