/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.hpp
*/

#pragma once

#include "util/Config.hpp"
#include <netinet/in.h>
#include <vector>

class UdpSocket {
  public:
    explicit UdpSocket(Config port = PORT);
    ~UdpSocket();

    void init();
    void listen();
    void close();

  private:
    Config port;

    int udpSocket;
    sockaddr_in udpAddr;
};
