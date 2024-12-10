/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerManager.hpp
*/

/**
 * @file PlayerManager.hpp
 * @brief Declaration of the PlayerManager class for managing player instances.
 */

#pragma once

#include "component/player/Player.hpp"
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>

/**
 * @class PlayerManager
 * @brief Singleton class responsible for managing players.
 *
 * The PlayerManager class handles creation, removal, and retrieval of players.
 * It also ensures that a player is tied to a specific thread to avoid
 * duplications.
 */
class PlayerManager {
  public:
    /**
     * @brief Get the singleton instance of the PlayerManager.
     *
     * @return A reference to the singleton PlayerManager instance.
     */
    static PlayerManager& getInstance();

    /**
     * @brief Create a new player with the given ID and name.
     *
     * @param userId The unique identifier for the new player.
     * @param name The name of the player.
     * @return A shared pointer to the newly created Player, or nullptr if the
     * player already exists.
     */
    std::shared_ptr<Player> createPlayer(int32_t userId,
                                         const std::string& name);

    /**
     * @brief Remove a player by their ID.
     *
     * @param userId The unique identifier of the player to remove.
     * @return True if the player was removed successfully, false otherwise.
     */
    bool removePlayer(int32_t userId);

    /**
     * @brief Find a player by their ID.
     *
     * @param userId The unique identifier of the player to find.
     * @return A shared pointer to the Player, or nullptr if not found.
     */
    std::shared_ptr<Player> findPlayerById(int32_t userId) const;

    /**
     * @brief Find or create a player associated with the current thread.
     *
     * If a player is already associated with the thread, it is returned.
     * Otherwise, a new player is created and associated with the thread.
     *
     * @param name The name to assign to a new player, if created.
     * @return A shared pointer to the existing or newly created Player.
     */
    std::shared_ptr<Player> createPlayerByThread(const std::string& name);

    /**
     * @brief Get a map of all players managed by the PlayerManager.
     *
     * @return A constant reference to the unordered map of players, keyed by
     * their IDs.
     */
    const std::unordered_map<int32_t, std::shared_ptr<Player>>&
    getPlayers() const;

  private:
    /**
     * @brief Private constructor for the singleton pattern.
     */
    PlayerManager();

    /**
     * @brief Destructor for the PlayerManager.
     */
    ~PlayerManager();

    /**
     * @brief Deleted copy constructor to prevent copying.
     */
    PlayerManager(const PlayerManager&) = delete;

    /**
     * @brief Deleted assignment operator to prevent assignment.
     */
    PlayerManager& operator=(const PlayerManager&) = delete;

    std::unordered_map<int32_t, std::shared_ptr<Player>>
        _players; ///< Map of players by their IDs.
    std::unordered_map<std::thread::id, int32_t>
        _threadIds;            ///< Map of thread IDs to player IDs.
    std::mutex _mutex;         ///< Mutex for thread-safe operations.
    int32_t _nextPlayerId = 1; ///< Counter for generating unique player IDs.
};
