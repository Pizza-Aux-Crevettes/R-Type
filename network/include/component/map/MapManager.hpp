/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapManager.hpp
*/

#pragma once

#include <memory>
#include "component/map/Map.hpp"

class MapManager {
  public:
    MapManager(const MapManager&) = delete;
    MapManager& operator=(const MapManager&) = delete;

    static MapManager& get();

    std::shared_ptr<Map> loadMap(int mapId);

  private:
    MapManager() = default;
    ~MapManager() = default;
};
