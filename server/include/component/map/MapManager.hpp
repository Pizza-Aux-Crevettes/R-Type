/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapManager.hpp
*/

#pragma once

#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include "component/map/Map.hpp"

class MapManager {
  public:
    MapManager(const MapManager&) = delete;
    MapManager& operator=(const MapManager&) = delete;

    static MapManager& get();

    void preloadMapsFromFolder(const std::string& folderPath);
    std::shared_ptr<Map> getMapById(int mapId) const;

  private:
    MapManager() = default;
    ~MapManager() = default;

    std::shared_ptr<Map> loadMapFromFile(const std::string& filePath);

    std::unordered_map<int, std::shared_ptr<Map>> _maps;
};
