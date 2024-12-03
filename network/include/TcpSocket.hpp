/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TcpSocket.hpp
*/

#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP

#include <vector>
#include <thread>
#include <netinet/in.h>
#include "Config.hpp"

class TcpSocket {
public:
    explicit TcpSocket(Config port = PORT);
    ~TcpSocket();

    void init();
    void listen();
    void close();

private:
    Config port;
    int tcpSocket;
    sockaddr_in tcpAddr;
    std::vector<std::thread> clientThreads;

    void handleClient(int clientSocket);
};

#endif // TCPSOCKET_HPP
