/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Client.hpp
*/

#pragma once

#include <arpa/inet.h>
#include <memory>
#include <netinet/in.h>
#include "component/player/Player.hpp"

class Client {
  public:
    Client(int tcpSocket, const sockaddr_in& udpAddr);

    int getTcpSocket() const;
    const sockaddr_in& getUdpAddr() const;
    std::shared_ptr<Player> getPlayer() const;

    void setTcpSocket(int socket);
    void setUdpAddr(const sockaddr_in& addr);
    void setPlayer(std::shared_ptr<Player> player);

    bool hasSameUdpEndpoint(const sockaddr_in& other) const;

  private:
    int _tcpSocket;
    sockaddr_in _udpAddr;
    std::shared_ptr<Player> _player;
};
