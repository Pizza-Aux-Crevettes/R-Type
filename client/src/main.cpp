/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Client.cpp
*/

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
        networkClient.run();

        Client client;
        client.manageClient();
    } catch (const std::exception& e) {
        Logger::error("[Main] Error: " + std::string(e.what()));
        return FAILURE;
    }

    return SUCCESS;
}