/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.hpp
*/

#pragma once

#include "util/Config.hpp"
#include <netinet/in.h>
#include <thread>
#include <vector>

class TcpSocket {
  public:
    TcpSocket(Config port = PORT);
    ~TcpSocket();

    void init();
    void listen();
    void close();

  private:
    Config port;

    int tcpSocket;
    sockaddr_in tcpAddr;

    std::vector<std::thread> clientThreads;
    void handleClient(int clientSocket);
};
