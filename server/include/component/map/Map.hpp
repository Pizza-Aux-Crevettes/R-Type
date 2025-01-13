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
    Map(const std::string& name,
        const std::vector<std::shared_ptr<Obstacle>>& obstacles);

    void incrementViewport();
    int32_t getViewport() const;
    std::vector<std::shared_ptr<Obstacle>> getObstaclesByViewport() const;
    bool isVoidBlock(int32_t x, int32_t y) const;

  private:
    std::string _name;
    int32_t _viewport;
    std::vector<std::shared_ptr<Obstacle>> _obstacles;

    static constexpr int RENDER_DISTANCE = 10;
};
