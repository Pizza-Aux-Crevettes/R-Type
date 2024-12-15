/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.hpp
*/

#pragma once

#include <SmartBuffer.hpp>
#include <netinet/in.h>

class TcpSocket {
  public:
    TcpSocket();
    ~TcpSocket();

    static void send(int clientSocket, const SmartBuffer& smartBuffer);
    void init();
    [[noreturn]] void readLoop() const;
    void close() const;

  private:
    int _tcpSocket;
    sockaddr_in _tcpAddr{};

    static void handleClientRead(int clientSocket);
};
