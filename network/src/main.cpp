/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** main.cpp
*/

#include "socket/Server.hpp"
#include "util/Logger.hpp"
#include <iostream>

int main() {
    Logger::info("[Main] Starting server...");

    try {
        Server server(PORT);
        Logger::success("[Main] Server successfully initialized on port " + std::to_string(PORT) + ".");

        server.start();
    } catch (const std::exception& e) {
        Logger::error("[Main] Critical server error: " + std::string(e.what()));
        return FAILURE;
    } catch (...) {
        Logger::error("[Main] An unknown error occurred.");
        return FAILURE;
    }

    Logger::success("[Main] Server stopped successfully.");
    return SUCCESS;
}
