/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Map.hpp
*/

#pragma once

#include <string>
#include <vector>
#include "component/obstacle/Obstacle.hpp"

class Map {
  public:
    Map(const std::string& name, int width, int height, int blockSize);
    ~Map() = default; 

    void updateViewport();
    [[nodiscard]] int getViewport() const;
    [[nodiscard]] std::vector<Obstacle> getVisibleBlocks(int range) const;

  private:
    std::string _name;
    int _width;
    int _height;
    int _blockSize;
    int _viewport;
    std::vector<std::vector<Obstacle>> _blocks;
};
