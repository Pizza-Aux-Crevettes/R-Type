/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.hpp
*/

#pragma once

#include <SmartBuffer.hpp>
#include <arpa/inet.h>
#include <memory>
#include <mutex>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>
#include <vector>

class TcpSocket {
  public:
    TcpSocket();
    ~TcpSocket();

    void init();
    void readLoop() const;
    static void sendToOne(int clientSocket, const SmartBuffer& smartBuffer);
    static void sendToAll(const SmartBuffer& smartBuffer);
    static std::vector<int> getClients();
    void close() const;

  private:
    int _tcpSocket;
    sockaddr_in _tcpAddr{};
    static std::vector<int> _clients;
    static std::mutex _clientsMutex;

    static void handleRead(int clientSocket, SmartBuffer& smartBuffer,
                           const sockaddr_in& clientAddr);
    static void addClient(int clientSocket);
    static void removeClient(int clientSocket);
};