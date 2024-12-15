/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Server.hpp
*/

#pragma once

#include "socket/TcpSocket.hpp"
#include "socket/UdpSocket.hpp"
#include <thread>
#include <vector>

class Server {
  public:
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    static Server& getInstance();
    int start();

  private:
    Server();
    ~Server();

    TcpSocket _tcpSocket;
    UdpSocket _udpSocket;
    std::vector<std::thread> _threads;

    void closeThreads();
};
