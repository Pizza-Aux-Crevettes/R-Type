/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Map.cpp
*/

#include "component/map/Map.hpp"

Map::Map(const std::string& name, int width, int height, int blockSize)
    : _name(name), _width(width), _height(height), _blockSize(blockSize), _viewport(0) {
    _blocks.resize(height, std::vector<Obstacle>(width, Obstacle()));
}

void Map::updateViewport() {
    _viewport += 1;
}

int Map::getViewport() const {
    return _viewport;
}

std::vector<Obstacle> Map::getVisibleBlocks(int range) const {
    std::vector<Obstacle> visibleBlocks;
    int startX = _viewport / _blockSize;
    int endX = startX + range;

    for (int x = startX; x < endX && x < _width; ++x) {
        for (int y = 0; y < _height; ++y) {
            if (_blocks[y][x].getType() != ObstacleType::NONE) {
                visibleBlocks.push_back(_blocks[y][x]);
            }
        }
    }
    
    return visibleBlocks;
}
