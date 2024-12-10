/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerManager.hpp
*/

#pragma once

#include "component/player/Player.hpp"
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>

class PlayerManager {
  public:
    static PlayerManager& getInstance();

    std::shared_ptr<Player> createPlayer(int32_t userId,
                                         const std::string& name);
    bool removePlayer(int32_t userId);

    std::shared_ptr<Player> findPlayerById(int32_t userId) const;
    std::shared_ptr<Player> findPlayerByThread(const std::string& name);

    const std::unordered_map<int32_t, std::shared_ptr<Player>>&
    getPlayers() const;

  private:
    PlayerManager();
    ~PlayerManager();

    PlayerManager(const PlayerManager&) = delete;
    PlayerManager& operator=(const PlayerManager&) = delete;

    std::unordered_map<int32_t, std::shared_ptr<Player>> _players;
    std::unordered_map<std::thread::id, int32_t> _threadIds;
    std::mutex _mutex;
    int32_t _nextPlayerId;
};