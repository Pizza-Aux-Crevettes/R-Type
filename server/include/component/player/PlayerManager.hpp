/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerManager.hpp
*/

#pragma once

#include <algorithm>
#include <memory>
#include <ranges>
#include <unordered_map>
#include "component/player/Player.hpp"

class PlayerManager {
  public:
    PlayerManager(const PlayerManager&) = delete;
    PlayerManager& operator=(const PlayerManager&) = delete;

    static PlayerManager& get();

    std::shared_ptr<Player> createPlayer(const std::string& name);
    std::shared_ptr<Player> findPlayerById(int playerId) const;
    bool removePlayer(int playerId);
    const std::unordered_map<int, std::shared_ptr<Player>>& getPlayers() const;
    void movePlayer(int playerId, int offsetX, int offsetY);

  private:
    PlayerManager() = default;
    ~PlayerManager() = default;

    std::unordered_map<int, std::shared_ptr<Player>> _players;
};
