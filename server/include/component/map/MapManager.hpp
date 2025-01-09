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
#include <vector>
#include "component/map/Map.hpp"
#include "component/obstacle/Obstacle.hpp"

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
    void parseMapLine(const std::string& line, int y,
                      std::vector<Obstacle>& obstacles);

    std::unordered_map<int, std::shared_ptr<Map>> _maps;

    static inline const std::unordered_map<std::string, ObstacleType>
        _obstacleMapping = {
            {"0001", ObstacleType::BLOCK},
            {"0002", ObstacleType::BLOCK2},
            {"0003", ObstacleType::BLOCK3},
            {"0004", ObstacleType::BLOCK4},
    };

    static constexpr char NAME_LABEL[] = "name=";
    static constexpr char MAP_LABEL[] = "map=###";
    static constexpr char END_LABEL[] = "###";
    static constexpr int NAME_OFFSET = 5;
    static constexpr int BLOCK_OFFSET = 4;
};
