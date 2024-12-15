/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.hpp
*/

#pragma once

#include "Socket.hpp"
#include <SmartBuffer.hpp>

class UdpSocket : public Socket {
  public:
    UdpSocket(const std::string& serverAddress, int port);
    ~UdpSocket() override;

    void init();
    void sendBuffer(const SmartBuffer& smartBuffer);
    SmartBuffer receiveBuffer();
};
