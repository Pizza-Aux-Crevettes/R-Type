/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Server.hpp
*/

#pragma once

#include "protocol/Protocol.hpp"
#include "socket/TcpSocket.hpp"
#include "socket/UdpSocket.hpp"
#include <thread>
#include <vector>

class Server {
  public:
    static Server& getInstance();

    int start();

  private:
    Server();
    ~Server();
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    TcpSocket _tcpSocket;
    UdpSocket _udpSocket;
    std::vector<std::thread> _clientThreads;

    void closeThreads();
};
