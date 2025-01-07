/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Map.hpp
*/

#pragma once

#include <string>
#include <vector>
#include <memory>
#include "component/obstacle/Obstacle.hpp"

class Map {
  public:
    Map(const std::string& name, const std::vector<Obstacle>& obstacles);

    void incrementViewport();
    int getViewport() const;
    const std::vector<Obstacle>& getObstacles() const;

  private:
    std::string _name;
    std::vector<Obstacle> _obstacles;
    int _viewport;
};
