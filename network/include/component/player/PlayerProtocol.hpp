/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerProtocol.hpp
*/

#pragma once

#include <SmartBuffer.hpp>
#include <memory>
#include <vector>
#include "component/player/Player.hpp"
#include "socket/client/Client.hpp"

class PlayerProtocol {
  public:
    static void newPlayer(std::shared_ptr<Client> client,
                          SmartBuffer& smartBuffer);

    static void sendPlayerPositionUpdate(
        int udpSocket, const std::vector<std::shared_ptr<Player>>& players,
        const std::shared_ptr<Player>& player, SmartBuffer& smartBuffer);
};