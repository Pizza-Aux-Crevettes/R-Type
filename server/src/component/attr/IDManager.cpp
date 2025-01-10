/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** IDManager.cpp
*/

#include "component/attr/IDManager.hpp"

// Initialize the static atomic ID counter
std::atomic<int> IDManager::_currentId = 1;

/**
 * @brief Get the next available ID
 *
 * @return int The next available ID
 */
int IDManager::getNextId() {
    return _currentId++;
}
