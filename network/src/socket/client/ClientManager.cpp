/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** ClientManager.cpp
*/

#include "socket/client/ClientManager.hpp"

ClientManager& ClientManager::getInstance() {
    static ClientManager instance;
    return instance;
}

std::shared_ptr<Client> ClientManager::findOrCreateClient(const sockaddr_in &addr)
{
    std::lock_guard<std::mutex> lock(_clientsMutex);

    for (auto &[key, existingClient] : _clients) {
        const sockaddr_in &storedAddr = existingClient->getUdpAddr();
        if (storedAddr.sin_addr.s_addr == addr.sin_addr.s_addr) {
            Logger::info("[ClientManager] Found existing client by IP. Updating UDP port from " +
                         std::to_string(ntohs(storedAddr.sin_port)) + " to " +
                         std::to_string(ntohs(addr.sin_port)));

            existingClient->setUdpAddr(addr);
            return existingClient;
        }
    }

    std::string fullKey = generateKey(addr);
    auto newClient = std::make_shared<Client>(-1, addr);
    _clients[fullKey] = newClient;
    Logger::info("[ClientManager] New client created for key: " + fullKey);
    return newClient;
}

std::vector<std::shared_ptr<Client>> ClientManager::getAllClients() const {
    std::lock_guard<std::mutex> lock(_clientsMutex);

    std::vector<std::shared_ptr<Client>> clients;
    for (const auto& [key, client] : _clients) {
        clients.push_back(client);
    }

    return clients;
}

void ClientManager::removeClient(std::shared_ptr<Client> client) {
    std::lock_guard<std::mutex> lock(_clientsMutex);

    std::string key = generateKey(client->getUdpAddr());
    if (_clients.erase(key)) {
        Logger::info("[ClientManager] Removed client with key: " + key);
    } else {
        Logger::warning("[ClientManager] Failed to remove client with key: " + key);
    }
}

std::string ClientManager::generateKey(const sockaddr_in& addr) const {
    return std::string(inet_ntoa(addr.sin_addr)) + ":" +
           std::to_string(ntohs(addr.sin_port));
}
