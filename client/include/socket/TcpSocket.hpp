/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.hpp
*/

#pragma once

#include "Socket.hpp"
#include <SmartBuffer.hpp>

class TcpSocket : public Socket {
  public:
    TcpSocket(const std::string& serverAddress, int port);
    ~TcpSocket() override;

    void init();
    void connectSocket();
    void sendBuffer(const SmartBuffer& smartBuffer);
    SmartBuffer receiveBuffer();
};
