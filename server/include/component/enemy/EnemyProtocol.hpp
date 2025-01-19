/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** EnemyProtocol.hpp
*/

#pragma once

#include <SmartBuffer.hpp>
#include <memory>
#include <netinet/in.h>

class EnemyProtocol {
  public:
    static void sendEnemiesUpdate(const sockaddr_in& clientAddr,
                                  SmartBuffer& smartBuffer);
};
