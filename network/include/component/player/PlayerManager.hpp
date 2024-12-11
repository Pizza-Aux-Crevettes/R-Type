/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerManager.hpp
*/

#pragma once

#include "component/player/Player.hpp"
#include <thread>
#include <unordered_map>

class PlayerManager {
  public:
    PlayerManager(const PlayerManager&) = delete;
    PlayerManager& operator=(const PlayerManager&) = delete;

    static PlayerManager& getInstance();

    std::shared_ptr<Player> createPlayer(int32_t userId,
                                         const std::string& name);
    bool removePlayer(int32_t userId);
    [[nodiscard]] [[nodiscard]] std::shared_ptr<Player>
    findPlayerById(int32_t userId) const;
    std::shared_ptr<Player> createPlayerByThread(const std::string& name);
    [[nodiscard]] const std::unordered_map<int32_t, std::shared_ptr<Player>>&
    getPlayers() const;

  private:
    PlayerManager();
    ~PlayerManager();

    std::unordered_map<int32_t, std::shared_ptr<Player>> _players;
    std::unordered_map<std::thread::id, int32_t> _threadIds;
    std::mutex _mutex;
    int32_t _nextuserId = 1;
};
