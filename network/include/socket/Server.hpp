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
#include "util/Config.hpp"
#include <thread>
#include <vector>

class Server {
  public:
    Server();
    ~Server();

    int start();

    static Protocol& getProtocol();

  private:
    TcpSocket _tcpSocket;
    UdpSocket _udpSocket;

    static Protocol _protocol;

    std::vector<std::thread> _clientThreads;
    void closeThreads();
};
