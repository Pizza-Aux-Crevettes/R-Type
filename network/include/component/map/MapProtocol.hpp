/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapProtocol.hpp
*/

#pragma once

#include <SmartBuffer.hpp>
#include "component/map/MapManager.hpp"

class MapProtocol {
  public:
    static void sendViewportUpdate(int clientSocket, int viewport);
    static void sendBlocksUpdate(int clientSocket,
                                 const std::vector<Obstacle>& blocks);
};
