/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Config.hpp
*/

/**
 * @file Config.hpp
 * @brief Defines configuration constants used throughout the application.
 */

#pragma once

/**
 * @enum Config
 * @brief Contains global constants for configuration settings.
 *
 * This enum provides default values and settings for networking,
 * return codes, string handling, and game-related parameters.
 */
enum Config {
    // Network Configuration

    /**
     * @brief Default size of data buffers in bytes.
     */
    DEFAULT_BYTES = 1024,

    /**
     * @brief Default port number for network communication.
     */
    PORT = 8080,

    // Return Codes

    /**
     * @brief Return code indicating success.
     */
    SUCCESS = 0,

    /**
     * @brief Return code indicating a general error.
     */
    ERROR = 84,

    /**
     * @brief Return code indicating a failure.
     */
    FAILURE = -1,

    /**
     * @brief Return code for a bad or invalid result.
     */
    BAD = 1,

    // String Configuration

    /**
     * @brief Null character for string termination.
     */
    END_STR = '\0',

    // Game Configuration

    /**
     * @brief Default health for players or entities in the game.
     */
    DEFAULT_HEALTH = 100,

    /**
     * @brief Default number of lives for players.
     */
    DEFAULT_LIVES = 3,

    /**
     * @brief Default game frequency, representing FPS (frames per second).
     */
    DEFAULT_FREQUENCY = 60,
};
