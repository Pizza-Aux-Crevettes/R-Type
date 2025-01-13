/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Config.hpp
*/

#pragma once

enum Config {
    // Socket
    DEFAULT_BYTES = 1024,
    PORT = 8080,
    FPS = 60,

    // Program
    SUCCESS = 0,
    ERROR = 84,
    FAILURE = -1,
    BAD = 1,

    // String
    END_STR = '\0',

    // Player
    DEFAULT_HEALTH = 100,
    DEFAULT_LIVES = 3,
    PLAYER_SPEED = 10,

    // Map
    BLOCK_SIZE = 32,
    RENDER_DISTANCE = 10,

    // Bullet
    BULLET_SPEED = 60,
};
