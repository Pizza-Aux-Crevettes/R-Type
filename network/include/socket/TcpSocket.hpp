/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.hpp
*/

#pragma once

#include <SmartBuffer.hpp>
#include <netinet/in.h>
#include <vector>
#include <mutex>

class TcpSocket {
public:
    TcpSocket();
    ~TcpSocket();

    static void sendToOne(int clientSocket, const SmartBuffer& smartBuffer);
    static void sendToAll(const SmartBuffer& smartBuffer);
    void init();
    [[noreturn]] void readLoop() const;
    void close() const;
    static std::vector<int> getClients();

private:
    int _tcpSocket;
    sockaddr_in _tcpAddr{};
    static std::vector<int> _clients;
    static std::mutex _clientsMutex;

    static void handleRead(int clientSocket);
    static void addClient(int clientSocket);
    static void removeClient(int clientSocket);
};