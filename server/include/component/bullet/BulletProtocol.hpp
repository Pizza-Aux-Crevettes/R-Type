/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** BulletProtocol.hpp
*/

#pragma once

#include <SmartBuffer.hpp>
#include <memory>
#include <netinet/in.h>
#include "component/player/Player.hpp"

class BulletProtocol {
  public:
    static void sendBulletUpdate(const int udpSocket, const sockaddr_in& client,
                                 const std::shared_ptr<Player>& player,
                                 SmartBuffer& smartBuffer);
};
