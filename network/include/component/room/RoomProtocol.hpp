/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** RoomProtocol.hpp
*/

#pragma once

#include <SmartBuffer.hpp>
#include <string>

class RoomProtocol {
  public:
    static void createRoom(int clientSocket, SmartBuffer& smartBuffer);
    static void joinRoom(int clientSocket, SmartBuffer& smartBuffer);
    static void deleteRoom(int clientSocket, SmartBuffer& smartBuffer);
};
