/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** IDManager.cpp
*/

#include "component/attr/IDManager.hpp"

std::atomic<int32_t> IDManager::_currentId = 1;

/**
 * @brief Get the next available ID
 *
 * @return int32_t The next available ID
 */
int32_t IDManager::getNextId() {
    return _currentId++;
}
