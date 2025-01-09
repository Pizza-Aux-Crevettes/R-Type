/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Map.hpp
*/

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "component/obstacle/Obstacle.hpp"

class Map {
  public:
    Map(const std::string& name, const std::vector<Obstacle>& obstacles);

    void incrementViewport();
    int getViewport() const;
    const std::vector<Obstacle>& getObstacles() const;
    std::vector<Obstacle> getObstaclesByViewport() const;

  private:
    std::string _name;
    std::vector<Obstacle> _obstacles;
    int _viewport;

    static constexpr int RENDER_DISTANCE = 10;
};
