/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** RoomProtocol.hpp
*/

#pragma once

#include <SmartBuffer.hpp>
#include <memory>
#include "socket/Client.hpp"

class RoomProtocol {
  public:
    static void createRoom(std::shared_ptr<Client> client,
                           SmartBuffer& smartBuffer);
    static void joinRoom(std::shared_ptr<Client> client,
                         SmartBuffer& smartBuffer);
    static void deleteRoom(std::shared_ptr<Client> client,
                           SmartBuffer& smartBuffer);
    static void startGame(std::shared_ptr<Client> client,
                          SmartBuffer& smartBuffer);
    static void stopGame(std::shared_ptr<Client> client,
                         SmartBuffer& smartBuffer);
};
