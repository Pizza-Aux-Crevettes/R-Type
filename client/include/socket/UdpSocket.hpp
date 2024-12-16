/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.hpp
*/

#pragma once

#include <mutex>
#include <SmartBuffer.hpp>
#include "Socket.hpp"

class UdpSocket final : public Socket {
  public:
    UdpSocket(const std::string& serverAddress, int port);
    ~UdpSocket() override;

    void init();
    static void send(const SmartBuffer& smartBuffer);
    SmartBuffer receive();
};
