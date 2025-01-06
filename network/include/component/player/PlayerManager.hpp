/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerManager.hpp
*/

#pragma once

#include "component/player/Player.hpp"
#include <memory>
#include <unordered_map>

class PlayerManager {
  public:
    PlayerManager(const PlayerManager&) = delete;
    PlayerManager& operator=(const PlayerManager&) = delete;

    static PlayerManager& get();
    [[nodiscard]] int32_t getNextUserId() const;
    std::shared_ptr<Player> createPlayer(const std::string& name);
    bool removePlayer(int32_t userId);
    [[nodiscard]] std::shared_ptr<Player> findPlayerById(int32_t userId) const;
    [[nodiscard]] const std::unordered_map<int32_t, std::shared_ptr<Player>>&
    getPlayers() const;

  private:
    PlayerManager();
    ~PlayerManager();

    std::unordered_map<int32_t, std::shared_ptr<Player>> _players;
};
