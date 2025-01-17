/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Server.hpp
*/

#pragma once

#include <memory>
#include <thread>
#include <vector>
#include "socket/TcpSocket.hpp"
#include "socket/UdpSocket.hpp"

class Server {
  public:
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    static Server& get();

    int start();

  private:
    Server();
    ~Server();

    TcpSocket& _tcpSocket = TcpSocket::get();
    UdpSocket& _udpSocket = UdpSocket::get();
    std::vector<std::thread> _threads;

    void closeThreads();
};
