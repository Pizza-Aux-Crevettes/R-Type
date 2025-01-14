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
#include "network/protocol/NetworkClient.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"

int main() {
    try {
        Client client;
      
        client.manageClient();
    } catch (const std::exception& e) {
        Logger::error("[Main] Error: " + std::string(e.what()));

        return FAILURE;
    }

    return SUCCESS;
}
