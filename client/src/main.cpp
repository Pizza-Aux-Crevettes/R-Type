/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** main.cpp
*/

#include <SFML/Audio.hpp>
#include <components/Button.hpp>
#include <thread>
#include "System.hpp"
#include "components/Position.hpp"
#include "components/Sprite.hpp"
#include "components/Text.hpp"
#include "components/Texture.hpp"
#include "protocol/NetworkClient.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"

// void runNetworkClient(NetworkClient& networkClient, Client* client) {
//     try {
//         while (!Client::get().getIsPlayed())
//             ;
//         networkClient.run();
//     } catch (const std::exception& e) {
//         Logger::error("[Server Thread] Error: " + std::string(e.what()));
//     }
// }

// void initializeNetwork(NetworkClient& networkClient) {
//     networkClient.init();
//     networkClient.connectTCP();  
//     networkClient.connectUDP();

//     Logger::success("[Main] Network initialized successfully.");
// }

int main() {
    try {
        Client client;
        // NetworkClient networkClient(Client::get().getIp(), std::any_cast<int>(Client::get().getPort()));

        // initializeNetwork(networkClient);
        // std::thread serverThread(runNetworkClient, std::ref(networkClient),
        //                          &client);
        client.manageClient();

        // if (serverThread.joinable()) {
        //     serverThread.join();
        // }
    } catch (const std::exception& e) {
        Logger::error("[Main] Error: " + std::string(e.what()));

        return FAILURE;
    }

    return SUCCESS;
}
