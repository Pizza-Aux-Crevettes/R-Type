/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** NetworkClient.hpp
*/

#pragma once

#include "socket/TcpSocket.hpp"
#include "socket/UdpSocket.hpp"
#include "Client.hpp"

class NetworkClient {
  public:
    NetworkClient(const std::string& serverAddress, int serverPort);
    ~NetworkClient();

    void init();
    void connectTCP();
    static void connectUDP();
    void run(Client *client);

  private:
    TcpSocket tcpSocket;
    UdpSocket udpSocket;

    void handleTcpMessages(Client *client) const;
    void handleUdpMessages(Client *client);
};
