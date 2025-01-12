/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** IDManager.hpp
*/

#pragma once
#include <atomic>

class IDManager {
  public:
    static int32_t getNextId();

  private:
    static std::atomic<int32_t> _currentId;
};
