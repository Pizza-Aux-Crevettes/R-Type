/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** ObstacleManager.hpp
*/

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "component/obstacle/Obstacle.hpp"

class ObstacleManager {
  public:
    static ObstacleManager& get();

    std::string ObstacleTypeToString(ObstacleType type);
    void addObstacle(const std::shared_ptr<Obstacle>& obstacle);
    const std::vector<std::shared_ptr<Obstacle>>& getAllObstacles() const;
    const std::vector<std::shared_ptr<Obstacle>>& getVisibleObstacles() const;
    bool isObstacleCodeValid(const std::string& code) const;
    ObstacleType getObstacleType(const std::string& code) const;
    void updateObstacles();
    void forPlayers(const std::shared_ptr<Obstacle>& obstacle);
    void invalidate(const std::shared_ptr<Obstacle>& obstacle);
    int32_t getMaxMoveDistance(int32_t x, int32_t y, int32_t offsetX,
                               int32_t offsetY) const;
    double getViewport() const;

  private:
    ObstacleManager();
    ~ObstacleManager();

    double _viewport = 0;
    std::vector<std::shared_ptr<Obstacle>> _obstacles;
    std::vector<std::shared_ptr<Obstacle>> _visibleObstacles;
    std::unordered_map<std::string, ObstacleType> _obstacleMapping;
};
