/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerProtocol.hpp
*/

#pragma once

#include <SmartBuffer.hpp>
#include <memory>
#include <netinet/in.h>
#include "component/player/Player.hpp"

class PlayerProtocol {
  public:
    static void newPlayer(int clientSocket, SmartBuffer& smartBuffer);
    static void sendPlayerPosition(const sockaddr_in& clientAddr,
                                   SmartBuffer& smartBuffer);
    static void sendPlayerInfosUpdate(const std::shared_ptr<Player> player);
};
