/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** ObstacleManager.hpp
*/

#pragma once

#include "component/obstacle/Obstacle.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class ObstacleManager {
  public:
    static ObstacleManager& get();

    void addObstacle(const std::shared_ptr<Obstacle>& obstacle);
    std::vector<std::shared_ptr<Obstacle>> getObstacles() const;
    bool isObstacleCodeValid(const std::string& code) const;
    ObstacleType getObstacleType(const std::string& code) const;
    void reset();

  private:
    ObstacleManager();
    ~ObstacleManager() = default;

    std::vector<std::shared_ptr<Obstacle>> _obstacles;
    std::unordered_map<std::string, ObstacleType> _obstacleMapping;
};
