/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** main.cpp
*/

/**
 * @file main.cpp
 * @brief Entry point of the R-Type server application.
 *
 * This file initializes the application, starts the server, and handles
 * any critical errors during the initialization or runtime.
 */

#include "util/Config.hpp"
#include "util/Logger.hpp"
#include "util/Singletons.hpp"
#include <iostream>

/**
 * @brief Main entry point of the application.
 *
 * The `main` function initializes the application, starts the server,
 * and handles any exceptions or errors during the initialization phase.
 *
 * @return int Exit status of the application.
 * - `SUCCESS` (0) if the server starts and runs successfully.
 * - `FAILURE` (84) if any critical error occurs during startup.
 */
int main() {
    Logger::info("[Main] Starting application...");

    try {
        // Log server startup information
        Logger::success("[Main] Server successfully initialized on port " +
                        std::to_string(PORT) + ".");

        // Start the server
        Singletons::getServer().start();
    } catch (const std::exception& e) {
        // Handle and log critical exceptions
        Logger::error("[Main] Critical server error: " + std::string(e.what()));

        return FAILURE;
    } catch (...) {
        // Handle unknown errors
        Logger::error("[Main] An unknown error occurred.");

        return FAILURE;
    }

    return SUCCESS;
}
