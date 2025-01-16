/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapLoader.hpp
*/

#pragma once

#include <memory>
#include <string>

class MapLoader {
  public:
    static constexpr char NAME_LABEL[] = "name=";
    static constexpr char MAP_LABEL[] = "map=###";
    static constexpr char END_LABEL[] = "###";
    static constexpr int NAME_OFFSET = 5;
    static constexpr int OBSTACLE_OFFSET = 4;

    void loadMapFromFile(const std::string& filePath);
    void parseMapLine(const std::string& line, int32_t y);
};
