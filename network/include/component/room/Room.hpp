/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Room.hpp
*/

#pragma once

#include "component/player/Player.hpp"
#include <memory>
#include <string>
#include <vector>

class Room {
  public:
    Room(int id, const std::string& code, size_t capacity);

    int getId() const;
    const std::string& getCode() const;
    size_t getCapacity() const;
    const std::vector<std::shared_ptr<Player>>& getPlayers() const;

    bool addPlayer(const std::shared_ptr<Player>& player);
    bool removePlayer(const std::string& playerName);

  private:
    int _id;
    std::string _code;
    size_t _capacity;
    std::vector<std::shared_ptr<Player>> _players;
};
