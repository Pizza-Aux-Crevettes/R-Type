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
#include "util/Config.hpp"

class UdpSocket {
  public:
    UdpSocket(const UdpSocket&) = delete;
    UdpSocket& operator=(const UdpSocket&) = delete;

    static UdpSocket& get();

    void init();
    void run();
    void sendToOne(const sockaddr_in& clientAddrt,
                   const SmartBuffer& smartBuffer);
    void sendToAll(const SmartBuffer& smartBuffer);
    std::vector<sockaddr_in> getClients();
    void close() const;

  private:
    UdpSocket() = default;
    ~UdpSocket();

    int _udpSocket = FAILURE;
    sockaddr_in _udpAddr;
    std::vector<sockaddr_in> _clients;
    std::mutex _clientsMutex;

    void readLoop();
    void updateLoop();
    void sendLoop();
    void addClient(const sockaddr_in& clientAddr);
};
