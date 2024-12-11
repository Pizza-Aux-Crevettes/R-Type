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
    Room(const std::string& code, const std::shared_ptr<Player>& owner,
         size_t capacity, bool isPublic);

    const std::string& getCode() const;
    const std::shared_ptr<Player>& getOwner() const;
    size_t getCapacity() const;
    bool isPublic() const;
    const std::vector<std::shared_ptr<Player>>& getPlayers() const;
    bool addPlayer(const std::shared_ptr<Player>& player);
    bool removePlayer(const std::string& playerName);

  private:
    std::string _code;
    std::shared_ptr<Player> _owner;
    size_t _capacity;
    bool _isPublic;
    std::vector<std::shared_ptr<Player>> _players;
};
