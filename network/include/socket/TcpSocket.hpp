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
#include "socket/client/Client.hpp"

class TcpSocket {
public:
    TcpSocket();
    ~TcpSocket();

    void init();
    static void sendToOne(int clientSocket, const SmartBuffer& smartBuffer);
    static void sendToAll(const SmartBuffer& smartBuffer);
    [[noreturn]] void readLoop() const;
    void close() const;

private:
    int _tcpSocket;
    sockaddr_in _tcpAddr;

    void handleRead(std::shared_ptr<Client> client, SmartBuffer& smartBuffer) const;
};
