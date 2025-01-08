/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** ClientManager.cpp
*/

#pragma once

#include "socket/client/Client.hpp"
#include "util/Logger.hpp"
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

class ClientManager {
public:
    static ClientManager& getInstance();

    std::shared_ptr<Client> findOrCreateClient(const sockaddr_in& addr);
    std::vector<std::shared_ptr<Client>> getAllClients() const;
    void removeClient(std::shared_ptr<Client> client);

private:
    ClientManager() = default;
    ~ClientManager() = default;

    ClientManager(const ClientManager&) = delete;
    ClientManager& operator=(const ClientManager&) = delete;

    mutable std::mutex _clientsMutex;
    std::unordered_map<std::string, std::shared_ptr<Client>> _clients;

    std::string generateKey(const sockaddr_in& addr) const;
};
