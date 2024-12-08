/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Config.hpp
*/

#pragma once

enum Config {
    // Network
    DEFAULT_BYTES = 1024,
    PORT = 8080,

    // Return codes
    SUCCESS = 0,
    ERROR = 84,
    FAILURE = -1,
    BAD = 1,

    // String
    END_STR = '\0',

    // Game
    DEFAULT_HEALTH = 100,
    DEFAULT_LIVES = 3,
    DEFAULT_FREQUENCY = 60,
};
