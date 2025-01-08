/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.hpp
*/

#pragma once

#include <algorithm>
#include <arpa/inet.h>
#include <memory>
#include <mutex>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>
#include <vector>
#include "SmartBuffer.hpp"
#include "socket/Client.hpp"

class TcpSocket {
  public:
    TcpSocket();
    ~TcpSocket();

    void init();

    [[noreturn]] void readLoop() const;

    static void sendToOne(int clientSocket, const SmartBuffer& smartBuffer);
    static void sendToAll(const SmartBuffer& smartBuffer);

    void close() const;

  private:
    int _tcpSocket;
    sockaddr_in _tcpAddr;
    static std::vector<std::shared_ptr<Client>> _clients;
    static std::mutex _clientsMutex;

    void handleRead(std::shared_ptr<Client> client,
                    SmartBuffer& smartBuffer) const;
    void addClient(std::shared_ptr<Client> client) const;
    void removeClient(std::shared_ptr<Client> client) const;
};
