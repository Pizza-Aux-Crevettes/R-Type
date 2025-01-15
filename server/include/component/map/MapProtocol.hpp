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

class MapProtocol {
  public:
    static void sendViewportUpdate(const sockaddr_in& clientAddr,
                                   SmartBuffer& smartBuffer);
    static void sendEntityDeleted(int32_t entityId);
};
