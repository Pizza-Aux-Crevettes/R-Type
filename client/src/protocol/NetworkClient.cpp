/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** NetworkClient.cpp
*/

#include "protocol/NetworkClient.hpp"
#include <iostream>
#include <thread>
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

    SmartBuffer smartBuffer;

    // pour create un player
    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::NEW_PLAYER);
    smartBuffer << std::string{"Benjamin"};
    TcpSocket::send(smartBuffer);

    Logger::info("[NetworkClient] New player sent.");
}

void NetworkClient::connectUDP() {
    Logger::info("[NetworkClient] UDP initialized.");

    SmartBuffer smartBuffer;

    smartBuffer << static_cast<int16_t>(Protocol::OpCode::DEFAULT);
    UdpSocket::send(smartBuffer);
}

void NetworkClient::run() {
    std::thread tcpThread(&NetworkClient::handleTcpMessages, this);
    std::thread udpThread(&NetworkClient::handleUdpMessages, this);

    tcpThread.join();
    udpThread.join();
}

void NetworkClient::handleTcpMessages() const {
    try {
        while (true) {
            Logger::error("O");
            SmartBuffer buffer = tcpSocket.receive();
            Protocol::get().handleMessage(buffer);
        }
    } catch (const std::exception& e) {
        Logger::error("[NetworkClient] TCP Error: " + std::string(e.what()));
    }
}

void NetworkClient::handleUdpMessages() {
    try {
        while (true) {
            Logger::error("X");
            SmartBuffer buffer = udpSocket.receive();
            Protocol::get().handleMessage(buffer);
        }
    } catch (const std::exception& e) {
        Logger::error("[NetworkClient] UDP Error: " + std::string(e.what()));
    }
}
