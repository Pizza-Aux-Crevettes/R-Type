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
    bool isObstacleCodeValid(const std::string& code) const;
    ObstacleType getObstacleType(const std::string& code) const;
    void updateObstacles();
    double getViewport() const;
    bool isVoid(int32_t x, int32_t y) const;
    void reset();

  private:
    ObstacleManager();
    ~ObstacleManager() = default;

    double _viewport = 0;
    std::vector<std::shared_ptr<Obstacle>> _obstacles;
    std::vector<std::shared_ptr<Obstacle>> _visibleObstacles;
    std::vector<std::shared_ptr<Obstacle>> _previousVisibleObstacles;
    std::unordered_map<std::string, ObstacleType> _obstacleMapping;

    bool isInsideViewport(const std::shared_ptr<Obstacle>& obstacle,
                          double viewportStart, double viewportEnd) const;
};
