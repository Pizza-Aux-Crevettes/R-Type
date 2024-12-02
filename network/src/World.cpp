/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** World.cpp
*/

#include "World.hpp"

Point World::getSize() const {
    return size;
}

void World::setSize(const Point& newSize) {
    size = newSize;
}

std::vector<Obstacle>& World::getObstacles() const {
    return obstacleList;
}

void World::addObstacle(const Obstacle& obstacle) {
    obstacleList.push_back(obstacle);
}

std::vector<Checkpoint>& World::getCheckpoints() const {
    return checkpointList;
}

void World::addCheckpoint(const Checkpoint& checkpoint) {
    checkpointList.push_back(checkpoint);
}

std::vector<Player>& World::getPlayers() const {
    return playerList;
}

void World::addPlayer(const Player& player) {
    playerList.push_back(player);
}

std::vector<Enemy>& World::getEnemies() const {
    return enemyList;
}

void World::addEnemy(const Enemy& enemy) {
    enemyList.push_back(enemy);
}
