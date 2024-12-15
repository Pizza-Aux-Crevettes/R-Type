/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Singleton.hpp
*/

#pragma once

#include <mutex>
#include <netinet/in.h>

class Singleton {
  public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton& get();
    void setSavedTcpSocket(int tcpSocket);
    int getSavedTcpSocket() const;
    void setSavedUdpSocket(int udpSocket);
    int getSavedUdpSocket() const;
    void setSavedServerAddress(const sockaddr_in& serverAddress);
    sockaddr_in getSavedServerAddress() const;

  private:
    Singleton();
    ~Singleton();

    int _savedTcpSocket;
    int _savedUdpSocket;
    sockaddr_in _savedServerAddress;
    static std::mutex _mutex;
};
