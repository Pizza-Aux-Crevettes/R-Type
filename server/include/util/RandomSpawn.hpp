/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** RandomSpawn.hpp
*/

#pragma once

#include <random>
#include <util/Point.hpp>

class RandomSpawn {
  public:
    static const Point generateRandomSpawnPosition();
    static bool isSpawnFree(int x, int y);
};
