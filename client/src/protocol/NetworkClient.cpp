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

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::NEW_PLAYER)
                << std::string{"Benjamin"};
    TcpSocket::send(smartBuffer);

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::CREATE_ROOM)
                << static_cast<int32_t>(1) << static_cast<int16_t>(99)
                << static_cast<int16_t>(1) << static_cast<int16_t>(1);
    TcpSocket::send(smartBuffer);
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
            SmartBuffer buffer = udpSocket.receive();
            Protocol::get().handleMessage(buffer);
        }
    } catch (const std::exception& e) {
        Logger::error("[NetworkClient] UDP Error: " + std::string(e.what()));
    }
}
