/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** RoomManager.cpp
*/

#include "component/room/RoomManager.hpp"
#include "util/Logger.hpp"

RoomManager& RoomManager::getInstance() {
    static RoomManager instance;
    return instance;
}

RoomManager::RoomManager() : _nextRoomId(1) {}

RoomManager::~RoomManager() {}

std::shared_ptr<Room> RoomManager::createRoom(const std::string& code,
                                              size_t capacity) {
    auto room = std::make_shared<Room>(_nextRoomId++, code, capacity);

    _rooms.push_back(room);

    Logger::success(
        "[RoomManager] Created room with ID: " + std::to_string(room->getId()) +
        ", Code: " + code + ", Capacity: " + std::to_string(capacity) + ".");

    return room;
}

bool RoomManager::deleteRoom(int roomId) {
    auto it = std::remove_if(_rooms.begin(), _rooms.end(),
                             [roomId](const std::shared_ptr<Room>& room) {
                                 return room->getId() == roomId;
                             });

    if (it != _rooms.end()) {
        _rooms.erase(it, _rooms.end());

        Logger::success("[RoomManager] Deleted room with ID: " +
                        std::to_string(roomId) + ".");

        return true;
    }

    Logger::warning("[RoomManager] Failed to delete room with ID: " +
                    std::to_string(roomId) + ".");

    return false;
}

std::shared_ptr<Room> RoomManager::findRoomById(int roomId) {
    for (auto& room : _rooms) {
        if (room->getId() == roomId) {
            return room;
        }
    }

    return nullptr;
}

std::shared_ptr<Room> RoomManager::findRoomByCode(const std::string& code) {
    for (auto& room : _rooms) {
        if (room->getCode() == code) {
            return room;
        }
    }

    return nullptr;
}

const std::vector<std::shared_ptr<Room>>& RoomManager::getRooms() const {
    return _rooms;
}
