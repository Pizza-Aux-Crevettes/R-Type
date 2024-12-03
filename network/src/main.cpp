/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** main.cpp
*/

#include "Logger.hpp"
#include "Server.hpp"
#include <iostream>

int main() {
    try {
        Server server(PORT);
        server.start();
    } catch (const std::exception& e) {
        Logger::error(std::string("Server error: ") + e.what());
        return ERROR;
    }
    return SUCCESS;
}
