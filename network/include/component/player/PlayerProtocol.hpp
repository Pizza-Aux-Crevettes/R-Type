/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerProtocol.hpp
*/

#pragma once

#include "protocol/Protocol.hpp"
#include <SmartBuffer.hpp>

class PlayerProtocol {
  public:
    static void newPlayer(int clientSocket, SmartBuffer& smartBuffer);
};
