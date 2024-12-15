/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** NetworkClient.cpp
*/

#include <iostream>
#include <thread>
#include "protocol/NetworkClient.hpp"
#include "protocol/Protocol.hpp"
#include "util/Logger.hpp"

NetworkClient::NetworkClient(const std::string& serverAddress,
                             const int serverPort)
    : tcpSocket(serverAddress, serverPort),
      udpSocket(serverAddress, serverPort) {}

NetworkClient::~NetworkClient() {}

void NetworkClient::init() {
    tcpSocket.init();
    udpSocket.init();
}

void NetworkClient::connectTCP() {
    tcpSocket.connect();
    Logger::info("[NetworkClient] Connected to TCP server.");
}

void NetworkClient::connectUDP() {
    Logger::info("[NetworkClient] UDP initialized.");
}

void NetworkClient::run(Client *client) {
    std::thread tcpThread(&NetworkClient::handleTcpMessages, this, client);
    std::thread udpThread(&NetworkClient::handleUdpMessages, this, client);

    tcpThread.join();
    udpThread.join();
}

void NetworkClient::handleTcpMessages(Client *client) const {
    try {
        while (true) {
            SmartBuffer buffer = tcpSocket.receive();
            Protocol::get().handleMessage(buffer, client);
        }
    } catch (const std::exception& e) {
        Logger::error("[NetworkClient] TCP Error: " + std::string(e.what()));
    }
}

void NetworkClient::handleUdpMessages(Client *client) {
    try {
        while (true) {
            SmartBuffer buffer = udpSocket.receive();
            Protocol::get().handleMessage(buffer, client);
        }
    } catch (const std::exception& e) {
        Logger::error("[NetworkClient] UDP Error: " + std::string(e.what()));
    }
}
