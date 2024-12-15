/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Socket.hpp
*/

#pragma once

#include <netinet/in.h>
#include <string>

class Socket {
  public:
    Socket(const std::string& serverAddress, int port);
    virtual ~Socket();

    void close();

  protected:
    int _socket;
    sockaddr_in _serverAddr;
};
