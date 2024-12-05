#include "socket/Server.hpp"
#include "util/Logger.hpp"
#include <SmartBuffer.hpp>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

TcpSocket::TcpSocket(Config port) : port(port), tcpSocket(FAILURE) {
    Logger::socket("[TCP Socket] Instance created for port: " + std::to_string(port));
}

TcpSocket::~TcpSocket() {
    Logger::socket("[TCP Socket] Instance for port " + std::to_string(port) + " is being destroyed.");
    close();
}

void TcpSocket::init() {
    Logger::socket("[TCP Socket] Initializing socket on port: " + std::to_string(port));

    tcpSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (tcpSocket == FAILURE) {
        Logger::error("[TCP Socket] Failed to create socket.");
        throw std::runtime_error("Failed to create TCP socket.");
    }

    tcpAddr.sin_family = AF_INET;
    tcpAddr.sin_addr.s_addr = INADDR_ANY;
    tcpAddr.sin_port = htons(port);

    if (bind(tcpSocket, (struct sockaddr*)&tcpAddr, sizeof(tcpAddr)) < SUCCESS) {
        Logger::error("[TCP Socket] Failed to bind socket to port: " + std::to_string(port));
        throw std::runtime_error("Bind failed for TCP socket on port " + std::to_string(port));
    }

    if (::listen(tcpSocket, 3) < SUCCESS) {
        Logger::error("[TCP Socket] Failed to listen on port: " + std::to_string(port));
        throw std::runtime_error("Listen failed for TCP socket on port " + std::to_string(port));
    }

    Logger::socket("[TCP Socket] Successfully bound and listening on port: " + std::to_string(port));
}

void TcpSocket::listen() {
    Logger::socket("[TCP Socket] Waiting for incoming connections on port: " + std::to_string(port));

    while (true) {
        int clientSocket = accept(tcpSocket, nullptr, nullptr);

        if (clientSocket < SUCCESS) {
            Logger::warning("[TCP Socket] Failed to accept a connection.");
            continue;
        }

        Logger::socket("[TCP Socket] New client connected. Client socket: " + std::to_string(clientSocket));
        Logger::thread("[TCP Socket] Starting thread for client socket: " + std::to_string(clientSocket));

        clientThreads.emplace_back(
                [this, clientSocket]() { handleClient(clientSocket); });
    }
}

void TcpSocket::handleClient(int clientSocket) {
    SmartBuffer smartBuffer;

    Logger::thread("[TCP Socket] Handling client socket: " + std::to_string(clientSocket));

    while (true) {
        char rawBuffer[1024] = {0};
        int bytesRead = read(clientSocket, rawBuffer, sizeof(rawBuffer));

        if (bytesRead <= SUCCESS) {
            Logger::socket("[TCP Socket] Client disconnected. Socket: " + std::to_string(clientSocket));
            ::close(clientSocket);
            break;
        }

        Logger::packet("[TCP Socket] Received " + std::to_string(bytesRead) + " bytes from client socket: " + std::to_string(clientSocket));

        smartBuffer.inject(reinterpret_cast<const uint8_t*>(rawBuffer), bytesRead);
        smartBuffer.resetRead();

        Server::getProtocol().handleMessage(clientSocket, smartBuffer);
    }
}

void TcpSocket::close() {
    if (tcpSocket != FAILURE) {
        ::close(tcpSocket);
        Logger::socket("[TCP Socket] Socket on port " + std::to_string(port) + " successfully closed.");
    } else {
        Logger::warning("[TCP Socket] Attempted to close an uninitialized or already closed socket.");
    }
}
