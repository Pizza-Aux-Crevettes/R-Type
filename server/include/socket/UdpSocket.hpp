/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** UdpSocket.hpp
*/

#pragma once

#include <SmartBuffer.hpp>
#include <arpa/inet.h>
#include <chrono>
#include <memory>
#include <mutex>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>

class UdpSocket {
  public:
    UdpSocket();
    ~UdpSocket();

    void init();
    void readLoop();
    void sendLoop();
    static void sendToOne(int udpSocket, const sockaddr_in& clientAddr,
                          const SmartBuffer& smartBuffer);
    std::vector<sockaddr_in> getClients();
    void close() const;

  private:
    int _udpSocket;
    sockaddr_in _udpAddr{};
    std::vector<sockaddr_in> _clients;
    std::mutex _clientsMutex;

    void sendPlayerUpdates();
    void sendViewportUpdates();
    void sendObstaclesUpdates();
    void addClient(const sockaddr_in& clientAddr);
};
