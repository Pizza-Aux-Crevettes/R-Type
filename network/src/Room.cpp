#include "Room.hpp"

Room::Room(int32_t roomCode) : roomCode(roomCode) {}

void Room::addClient(int clientSocket) {
    std::lock_guard<std::mutex> lock(mutex);
    clients.push_back(clientSocket);
    Logger::info("Client added to room " + std::to_string(roomCode));
}

void Room::removeClient(int clientSocket) {
    std::lock_guard<std::mutex> lock(mutex);
    clients.erase(std::remove(clients.begin(), clients.end(), clientSocket),
                  clients.end());
    Logger::info("Client removed from room " + std::to_string(roomCode));
}

int32_t Room::getRoomCode() const {
    return roomCode;
}
