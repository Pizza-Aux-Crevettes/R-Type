/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Room.hpp
*/

#pragma once

#include "Logger.hpp"
#include <algorithm>
#include <mutex>
#include <vector>

class Room {
  public:
    explicit Room(int32_t roomCode);

    void addClient(int clientSocket);
    void removeClient(int clientSocket);

    int32_t getRoomCode() const;

  private:
    int32_t roomCode;
    std::vector<int> clients;
    std::mutex mutex;
};
