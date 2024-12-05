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
#include <SmartBuffer.hpp>
#include <thread>
#include <vector>

class Server {
  public:
    explicit Server(Config port = PORT);
    ~Server();

    int start();

    static Protocol& getProtocol();

  private:
    Config port;

    TcpSocket tcpSocket;
    UdpSocket udpSocket;

    SmartBuffer smartBuffer;
    static Protocol protocol;

    std::vector<std::thread> clientThreads;
    void closeThreads();
};
