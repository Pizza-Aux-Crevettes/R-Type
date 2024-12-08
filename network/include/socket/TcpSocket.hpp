/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.hpp
*/

#pragma once

#include <netinet/in.h>
#include <thread>
#include <vector>

class TcpSocket {
  public:
    TcpSocket();
    ~TcpSocket();

    void init();
    void listen();
    void close();

  private:
    int _tcpSocket;
    sockaddr_in _tcpAddr;

    std::vector<std::thread> _clientThreads;
    void handleClient(int clientSocket);
};
