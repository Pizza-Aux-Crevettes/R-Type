/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.hpp
*/

#pragma once

#include <algorithm>
#include <arpa/inet.h>
#include <chrono>
#include <memory>
#include <mutex>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>
#include <vector>
#include "SmartBuffer.hpp"
#include "socket/client/Client.hpp"

class UdpSocket {
public:
    UdpSocket();
    ~UdpSocket();

    void init();
    static void send(int udpSocket, const sockaddr_in& clientAddr,
                     const SmartBuffer& smartBuffer);
    [[noreturn]] void readLoop();
    [[noreturn]] void sendLoop();
    void close() const;

private:
    int _udpSocket;
    sockaddr_in _udpAddr;

    void handleRead(SmartBuffer& smartBuffer);
    void handleSend(SmartBuffer& smartBuffer);
};
