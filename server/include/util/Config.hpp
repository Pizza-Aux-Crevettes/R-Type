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

    // Server
    CADENCY = 20,
    TICK_PER_SECOND = 1000 / CADENCY,

    // Program
    SUCCESS = 0,
    ERROR = 84,
    FAILURE = -1,
    BAD = 1,
    END_STR = '\0',

    // Default
    DEFAULT_HEALTH = 100,
    DEFAULT_LIVES = 3,

    // Player
    PLAYER_WIDTH = 34,
    PLAYER_BULLET_SPEED = 10,
    PLAYER_BULLET_DAMAGE = 10,
    PLAYER_HEIGHT = 15,
    PLAYER_SPEED = 30,

    // Obstacle
    OBSTACLE_SIZE = 64,

    // Map
    RENDER_DISTANCE = 20,
    MAP_SPEED = 40,
    MAP_WIDTH = 1280,
    MAP_HEIGHT = 720,

    // Bullet
    BULLET_WIDTH = 50,
    BULLET_HEIGHT = 20,
};
