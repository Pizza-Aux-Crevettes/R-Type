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
    void loadMapFromFile(const std::string& filePath);
    void parseMapLine(const std::string& line, int32_t y);
};
