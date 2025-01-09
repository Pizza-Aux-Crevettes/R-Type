/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapProtocol.hpp
*/

#pragma once

#include <SmartBuffer.hpp>
#include <memory>
#include <netinet/in.h>
#include <thread>
#include "component/map/MapManager.hpp"

class MapProtocol {
  public:
    static void sendViewportUpdate(const int udpSocket,
                                   const sockaddr_in& clientAddr, int mapId,
                                   SmartBuffer& smartBuffer);
    static void sendObstaclesUpdate(const int udpSocket,
                                    const sockaddr_in& clientAddr, int mapId,
                                    SmartBuffer& smartBuffer);
};
