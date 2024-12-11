/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Player.hpp
*/

/**
 * @file Player.hpp
 * @brief Declaration of the Player class representing a player in the game.
 */

#pragma once

#include "component/attr/Health.hpp"
#include "util/Point.hpp"
#include <string>
#include <thread>

/**
 * @class Player
 * @brief Represents a player entity in the game.
 *
 * The Player class contains information about the player's ID, name, position,
 * size, speed, health, and the thread it is associated with.
 */
class Player {
  public:
    /**
     * @brief Constructs a Player instance with the specified attributes.
     *
     * @param userId The unique identifier for the player.
     * @param name The name of the player.
     * @param position The initial position of the player (default is (0, 0)).
     * @param size The size of the player (default is (0, 0)).
     * @param speed The movement speed of the player (default is 0).
     */
    Player(int32_t userId, const std::string& name,
           const Point& position = Point(), const Point& size = Point(),
           double speed = 0);

    /**
     * @brief Sets the position of the player.
     *
     * @param position The new position of the player.
     */
    void setPosition(const Point& position);

    /**
     * @brief Gets the current position of the player.
     *
     * @return The position of the player as a `Point`.
     */
    const Point& getPosition() const;

    /**
     * @brief Gets the thread ID associated with this player.
     *
     * @return The thread ID as a `std::thread::id`.
     */
    std::thread::id getThreadId() const;

    /**
     * @brief Sets the thread ID associated with this player.
     *
     * @param threadId The thread ID to associate with the player.
     */
    void setThreadId(const std::thread::id& threadId);

    /**
     * @brief Gets the unique ID of the player.
     *
     * @return The player's unique ID as an `int32_t`.
     */
    int32_t getId() const;

    /**
     * @brief Gets the name of the player.
     *
     * @return The player's name as a `std::string`.
     */
    const std::string& getName() const;

    /**
     * @brief Gets the size of the player.
     *
     * @return The player's size as a `Point`.
     */
    const Point& getSize() const;

    /**
     * @brief Gets the speed of the player.
     *
     * @return The player's speed as a `double`.
     */
    double getSpeed() const;

    /**
     * @brief Gets the health of the player.
     *
     * @return The player's health as a `Health` object.
     */
    const Health& getHealth() const;

    /**
     * @brief Moves the player by the specified deltas.
     *
     * @param deltaX The amount to move the player along the X-axis.
     * @param deltaY The amount to move the player along the Y-axis.
     */
    void move(double deltaX, double deltaY);

  private:
    int32_t _userId;           ///< Unique identifier for the player.
    std::string _name;         ///< Name of the player.
    Point _position;           ///< Position of the player.
    Point _size;               ///< Size of the player.
    double _speed;             ///< Movement speed of the player.
    Health _health;            ///< Health attributes of the player.
    std::thread::id _threadId; ///< ID of the thread associated with the player.
};
