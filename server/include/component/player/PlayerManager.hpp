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

    int32_t getNextUserId() const;
    std::shared_ptr<Player> createPlayer(const std::string& name);
    std::shared_ptr<Player> findPlayerById(int32_t playerId) const;
    bool removePlayer(int32_t playerId);

    const std::unordered_map<int32_t, std::shared_ptr<Player>>&
    getPlayers() const;

  private:
    PlayerManager() = default;
    ~PlayerManager() = default;

    std::unordered_map<int32_t, std::shared_ptr<Player>> _players;
};