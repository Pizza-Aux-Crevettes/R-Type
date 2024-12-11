/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.hpp
*/

/**
 * @file TcpSocket.hpp
 * @brief Declaration of the TcpSocket class for managing TCP socket
 * communication.
 */

#pragma once

#include <SmartBuffer.hpp>
#include <netinet/in.h>
#include <thread>
#include <vector>

class TcpSocket {
  public:
    TcpSocket();
    ~TcpSocket();

    static void sendTcp(int clientSocket, SmartBuffer& smartBuffer);

    void init();
    void listen();
    void close();

  private:
    int _tcpSocket;
    sockaddr_in _tcpAddr;
    std::vector<std::thread> _clientThreads;

    void handleClient(int clientSocket);
};
