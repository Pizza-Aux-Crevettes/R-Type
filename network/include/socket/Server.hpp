/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Server.hpp
*/

#pragma once

#include "protocol/Protocol.hpp"
#include "socket/TcpSocket.hpp"
#include "socket/UdpSocket.hpp"
#include <thread>
#include <vector>

class Server {
  public:
    static Server& getInstance();

    int start();

    void setFrequency(int frequency);
    int getFrequency() const;

    std::string getDateTime() const;
    std::string getPwd() const;
    double getMemoryUsageMB() const;
    double getMemoryUsagePercent() const;
    double getCpuUsagePercent() const;

  private:
    Server();
    ~Server();

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    TcpSocket _tcpSocket;
    UdpSocket _udpSocket;

    int _frequency;
    std::chrono::time_point<std::chrono::steady_clock> _lastUpdate;

    std::vector<std::thread> _clientThreads;
    void closeThreads();
};
