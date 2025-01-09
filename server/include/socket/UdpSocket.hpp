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
#include <netinet/in.h>
#include <thread>
#include <unistd.h>

class UdpSocket {
  public:
    UdpSocket();
    ~UdpSocket();

    static void send(int udpSocket, const sockaddr_in& clientAddr,
                     const SmartBuffer& smartBuffer);
    void init();
    void readLoop();
    void sendLoop();
    void close() const;
    void addClient(const sockaddr_in& clientAddr);
    std::vector<sockaddr_in> getClients();

  private:
    int _udpSocket;
    sockaddr_in _udpAddr{};
    std::vector<sockaddr_in> _clients;
    std::mutex _clientsMutex;

    void handleRead(SmartBuffer& smartBuffer);
    void handleSend(SmartBuffer& smartBuffer);
};
