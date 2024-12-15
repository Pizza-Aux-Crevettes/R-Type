/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Client.cpp
*/

#include <thread>
#include "Client.hpp"
#include "protocol/NetworkClient.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"

int main() {
    try {
        NetworkClient networkClient("127.0.0.1", SERVER_PORT);
        networkClient.init();
        networkClient.connectTCP();
        networkClient.connectUDP();

        Client client;

        std::thread serverThread([&networkClient]() {
            try {
                networkClient.run();
            } catch (const std::exception& e) {
                Logger::error("[Server Thread] Error: " + std::string(e.what()));
            }
        });

        client.manageClient();

        if (serverThread.joinable()) {
            serverThread.join();
        }
    } catch (const std::exception& e) {
        Logger::error("[Main] Error: " + std::string(e.what()));
        return FAILURE;
    }

    return SUCCESS;
}
