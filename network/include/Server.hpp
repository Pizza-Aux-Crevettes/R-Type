/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Server.hpp
*/

#pragma once

#include "Config.hpp"
#include "Protocol.hpp"
#include "TcpSocket.hpp"
#include "UdpSocket.hpp"
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

    void closeThreads();
    std::vector<std::thread> clientThreads;
};
