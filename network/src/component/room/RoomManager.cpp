/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** RoomManager.cpp
*/

#include "component/room/RoomManager.hpp"
#include "util/Logger.hpp"
#include <algorithm>
#include <random>

static constexpr char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                  "0123456789";

RoomManager& RoomManager::getInstance() {
    static RoomManager instance;
    return instance;
}

RoomManager::RoomManager() = default;

RoomManager::~RoomManager() = default;

std::string RoomManager::generateUniqueCode() const {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, sizeof(charset) - 2);

    while (true) {
        std::string code;

        for (size_t i = 0; i < 6; ++i) {
            code += charset[dist(rng)];
        }
        if (std::ranges::none_of(_rooms,
                                 [&code](const std::shared_ptr<Room>& room) {
                                     return room->getCode() == code;
                                 })) {
            return code;
        }
    }
}

std::shared_ptr<Room>
RoomManager::createRoom(const std::shared_ptr<Player>& owner, size_t capacity,
                        bool isPublic) {
    std::string code = generateUniqueCode();
    auto room = std::make_shared<Room>(code, owner, capacity, isPublic);

    _rooms.push_back(room);

    Logger::success("[RoomManager] Created room with code " + code +
                    ", Owner: " + owner->getName() +
                    ", Capacity: " + std::to_string(capacity) +
                    ", Public: " + (isPublic ? "true" : "false"));

    return room;
}

bool RoomManager::deleteRoom(const std::string& roomCode,
                             const std::shared_ptr<Player>& requester) {
    const auto it = std::ranges::find_if(
        _rooms, [&roomCode](const std::shared_ptr<Room>& room) {
            return room->getCode() == roomCode;
        });

    if (it != _rooms.end()) {
        if ((*it)->getOwner() == requester) {
            _rooms.erase(it);

            Logger::success("[RoomManager] Deleted room with code " + roomCode);

            return true;
        }

        return false;
    }

    Logger::warning("[RoomManager] Room not found with code: " + roomCode);

    return false;
}

std::shared_ptr<Room>
RoomManager::findRoomByCode(const std::string& code) const {
    for (const auto& room : _rooms) {
        if (room->getCode() == code) {
            return room;
        }
    }

    Logger::warning("[RoomManager] Room not found with code: " + code);

    return nullptr;
}

const std::vector<std::shared_ptr<Room>>& RoomManager::getRooms() const {
    return _rooms;
}
