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

    static void send(int clientSocket, SmartBuffer& smartBuffer);

    void init();
    void readLoop();
    void close();

  private:
    int _tcpSocket;
    sockaddr_in _tcpAddr;

    void handleClientRead(int clientSocket);
};
