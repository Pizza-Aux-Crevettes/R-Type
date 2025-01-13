/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapFileLoader.hpp
*/

#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>
#include "component/map/Map.hpp"

class MapFileLoader {
  public:
    std::vector<std::shared_ptr<Map>>
    loadMapsFromFolder(const std::string& folderPath);
    std::shared_ptr<Map> loadMapFromFile(const std::string& filePath);

  private:
    static constexpr char NAME_LABEL[] = "name=";
    static constexpr char MAP_LABEL[] = "map=###";
    static constexpr char END_LABEL[] = "###";
    static constexpr int NAME_OFFSET = 5;
    static constexpr int BLOCK_OFFSET = 4;

    void parseMapLine(const std::string& line, int32_t y,
                      std::vector<std::shared_ptr<Obstacle>>& obstacles);
};
