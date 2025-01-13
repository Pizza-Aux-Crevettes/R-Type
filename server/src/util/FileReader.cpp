/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** FileReader.cpp
*/

#include "util/FileReader.hpp"
#include <stdexcept>

/**
 * @brief Construct a new FileReader:: File Reader object
 *
 * @param filePath The file path
 */
FileReader::FileReader(const std::string& filePath) : _file(filePath) {
    if (!_file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
}

/**
 * @brief Read all lines from the file
 *
 * @return std::vector<std::string> The lines
 */
std::vector<std::string> FileReader::readAllLines() {
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(_file, line)) {
        lines.push_back(line);
    }

    return lines;
}
