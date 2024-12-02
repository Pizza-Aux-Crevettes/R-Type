/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** World.hpp
*/

#ifndef WORLD_HPP
#define WORLD_HPP

#include "Checkpoint.hpp"
#include "Enemy.hpp"
#include "Obstacle.hpp"
#include "Player.hpp"
#include "Point.hpp"
#include <vector>

class World {
  private:
    Point size;
    std::vector<Obstacle> obstacleList;
    std::vector<Checkpoint> checkpointList;
    std::vector<Player> playerList;
    std::vector<Enemy> enemyList;

  public:
    Point getSize() const;
    void setSize(const Point& size);

    std::vector<Obstacle>& getObstacles() const;
    void addObstacle(const Obstacle& obstacle);

    std::vector<Checkpoint>& getCheckpoints() const;
    void addCheckpoint(const Checkpoint& checkpoint);

    std::vector<Player>& getPlayers() const;
    void addPlayer(const Player& player);

    std::vector<Enemy>& getEnemies() const;
    void addEnemy(const Enemy& enemy);
};

#endif // WORLD_HPP
