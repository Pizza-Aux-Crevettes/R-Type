/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** main.cpp
*/

#include "component/map/MapLoader.hpp"
#include "socket/Server.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"

/**
 * @brief Main function
 *
 * @return int
 */
int main() {
    Logger::info("[Main] Starting application...");

    try {
        Logger::success("[Main] Server successfully initialized on port " +
                        std::to_string(PORT) + ".");

        MapLoader mapLoader;
        mapLoader.loadMapFromFile("./server/maps/map1.map");

        Server::get().start();
    } catch (const std::exception& e) {
        Logger::error("[Main] Critical server error: " + std::string(e.what()));
        return FAILURE;
    } catch (...) {
        Logger::error("[Main] An unknown error occurred.");
        return FAILURE;
    }

    return SUCCESS;
}
