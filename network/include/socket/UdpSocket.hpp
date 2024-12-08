/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.hpp
*/

#pragma once

#include <SmartBuffer.hpp>
#include <netinet/in.h>
#include <vector>

class UdpSocket {
  public:
    UdpSocket();
    ~UdpSocket();

    static void sendUdp(int udpSocket, const sockaddr_in& clientAddr,
                        SmartBuffer& smartBuffer);

    void init();
    void listen();
    void close();

  private:
    int _udpSocket;
    sockaddr_in _udpAddr;
};
