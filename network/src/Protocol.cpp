#include "Protocol.hpp"
#include "Logger.hpp"
#include <stdexcept>

Protocol::Protocol() {}

void Protocol::handleMessage(int clientSocket, SmartBuffer& smartBuffer) {
    int8_t opCode;
    smartBuffer >> opCode;

    switch (opCode) {
    case CREATE_ROOM:
        createRoom(clientSocket, smartBuffer);
        break;
    case JOIN_ROOM:
        joinRoom(clientSocket, smartBuffer);
        break;
    case DELETE_ROOM:
        deleteRoom(clientSocket, smartBuffer);
        break;
    default:
        Logger::warning("Received unknown OpCode: " + std::to_string(opCode));
    }
}

void Protocol::createRoom(int clientSocket, SmartBuffer& smartBuffer) {
    int32_t roomCode;
    smartBuffer >> roomCode;

    std::lock_guard<std::mutex> lock(roomMutex);
    if (rooms.find(roomCode) == rooms.end()) {
        rooms[roomCode] = std::make_shared<Room>(roomCode);
        Logger::info("Room created with code: " + std::to_string(roomCode));
    } else {
        Logger::warning("Room with code " + std::to_string(roomCode) +
                        " already exists.");
    }
}

void Protocol::joinRoom(int clientSocket, SmartBuffer& smartBuffer) {
    int32_t roomCode;
    smartBuffer >> roomCode;

    std::lock_guard<std::mutex> lock(roomMutex);
    auto it = rooms.find(roomCode);
    if (it != rooms.end()) {
        it->second->addClient(clientSocket);
    } else {
        Logger::warning("Room with code " + std::to_string(roomCode) +
                        " not found.");
    }
}

void Protocol::deleteRoom(int clientSocket, SmartBuffer& smartBuffer) {
    int32_t roomCode;
    smartBuffer >> roomCode;

    std::lock_guard<std::mutex> lock(roomMutex);
    if (rooms.erase(roomCode)) {
        Logger::info("Room with code " + std::to_string(roomCode) +
                     " deleted.");
    } else {
        Logger::warning("Attempted to delete non-existing room with code " +
                        std::to_string(roomCode));
    }
}
