/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Server.hpp
*/

#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <thread>
#include "TcpSocket.hpp"
#include "UdpSocket.hpp"
#include "SmartBuffer.hpp"
#include "Config.hpp"

class Server {
public:
    explicit Server(Config port = PORT);
    ~Server();

    int start();

private:
    Config port;
    TcpSocket tcpSocket;
    UdpSocket udpSocket;
    SmartBuffer smartBuffer;
    std::vector<std::thread> clientThreads;

    void closeThreads();
};

#endif // SERVER_HPP
