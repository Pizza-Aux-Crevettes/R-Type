/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.hpp
*/

#pragma once

#include <SmartBuffer.hpp>
#include <algorithm>
#include <arpa/inet.h>
#include <memory>
#include <mutex>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>
#include <vector>
#include "util/Config.hpp"

class TcpSocket {
  public:
    TcpSocket(const TcpSocket&) = delete;
    TcpSocket& operator=(const TcpSocket&) = delete;

    static TcpSocket& get();

    void init();
    void readLoop() const;
    void sendToOne(const int clientSocket, const SmartBuffer& smartBuffer);
    void sendToAll(const SmartBuffer& smartBuffer);
    std::vector<int> getClients();
    void close() const;

  private:
    TcpSocket() = default;
    ~TcpSocket();

    int _tcpSocket = FAILURE;
    sockaddr_in _tcpAddr{};
    std::vector<int> _clients;
    std::mutex _clientsMutex;

    void handleRead(const int clientSocket, SmartBuffer& smartBuffer);
    void addClient(const int clientSocket);
    void removeClient(const int clientSocket);
};
