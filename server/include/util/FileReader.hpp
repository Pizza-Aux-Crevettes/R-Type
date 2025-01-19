/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** FileReader.hpp
*/

#pragma once

#include <fstream>
#include <string>
#include <vector>

class FileReader {
  public:
    explicit FileReader(const std::string& filePath);
    std::vector<std::string> readAllLines();

  private:
    std::ifstream _file;
};
