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
#include <vector>
#include "component/player/Player.hpp"

class PlayerProtocol {
  public:
    static void newPlayer(int clientSocket, SmartBuffer& smartBuffer,
                          const sockaddr_in& clientAddr);
    static void updatePos(const int udpSocket,
                          const std::vector<std::shared_ptr<Player>>& players,
                          const std::shared_ptr<Player>& player,
                          SmartBuffer& smartBuffer);
};
