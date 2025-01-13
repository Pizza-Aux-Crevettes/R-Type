/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.hpp
*/

#pragma once

#include <SmartBuffer.hpp>
#include "Socket.hpp"

class TcpSocket final : public Socket {
  public:
    TcpSocket(const std::string& serverAddress, int port);
    ~TcpSocket() override;

    void init();
    void connect();
    static void send(const SmartBuffer& smartBuffer);
    SmartBuffer receive() const;
};
