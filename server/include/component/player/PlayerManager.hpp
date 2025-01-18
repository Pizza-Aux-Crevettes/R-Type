/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerManager.hpp
*/

#pragma once

#include <memory>
#include <vector>
#include "component/player/Player.hpp"

class PlayerManager {
  public:
    static PlayerManager& get();

    std::shared_ptr<Player> createPlayer(const std::string& name);
    std::shared_ptr<Player> findByID(int32_t playerId) const;
    bool removePlayer(int32_t playerId);
    void movePlayer(int32_t playerId, double offsetX, double offsetY);
    const std::vector<std::shared_ptr<Player>>& getPlayers() const;

  private:
    PlayerManager() = default;
    ~PlayerManager() = default;

    std::vector<std::shared_ptr<Player>> _players;
};
