/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** main.cpp
*/

#include "hypervisor/Hypervisor.hpp"
#include "socket/Server.hpp"
#include "util/Logger.hpp"
#include <QApplication>
#include <iostream>

int main(int ac, char** av) {
    int result = SUCCESS;

    Logger::info("[Main] Starting application...");

    QApplication app(ac, av);

    try {
        Server server;

        Logger::success("[Main] Server successfully initialized on port " +
                        std::to_string(PORT) + ".");

        Hypervisor hypervisor;
        hypervisor.show();
        result = app.exec();

        Logger::success("[Main] Hypervisor window displayed successfully.");

        server.start();
    } catch (const std::exception& e) {
        Logger::error("[Main] Critical server error: " + std::string(e.what()));

        return FAILURE;
    } catch (...) {
        Logger::error("[Main] An unknown error occurred.");

        return FAILURE;
    }

    return result;
}
