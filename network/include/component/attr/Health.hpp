/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Health.hpp
*/

/**
 * @file Health.hpp
 * @brief Declaration of the Health class representing a player's health system.
 */

#pragma once

#include "../../util/Config.hpp"

/**
 * @class Health
 * @brief Manages the health and lives of a player.
 *
 * The Health class provides methods to manage a player's current health,
 * lives, and the ability to determine if the player is still alive.
 */
class Health {
  public:
    /**
     * @brief Constructs a Health instance with specified initial values.
     *
     * @param health Initial health value (default is `DEFAULT_HEALTH`).
     * @param lives Initial number of lives (default is `DEFAULT_LIVES`).
     */
    Health(double health = DEFAULT_HEALTH, int lives = DEFAULT_LIVES);

    /**
     * @brief Destructor for the Health class.
     */
    ~Health();

    /**
     * @brief Gets the current health value.
     *
     * @return The player's current health as a `double`.
     */
    double getHealth() const;

    /**
     * @brief Gets the current number of lives.
     *
     * @return The player's current lives as an `int`.
     */
    int getLives() const;

    /**
     * @brief Reduces the player's health by a specified damage amount.
     *
     * If the resulting health is less than 0, it will be set to 0.
     *
     * @param damage The amount of damage to inflict on the player.
     */
    void takeDamage(double damage);

    /**
     * @brief Reduces the player's lives by one.
     */
    void loseLife();

    /**
     * @brief Checks if the player is still alive.
     *
     * A player is considered alive if they have either positive health or
     * remaining lives.
     *
     * @return `true` if the player is alive, `false` otherwise.
     */
    bool isAlive() const;

  private:
    double _health; ///< The player's current health value.
    int _lives;     ///< The player's remaining number of lives.
};
