/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** RoomManager.cpp
*/

#include "component/room/RoomManager.hpp"
#include "util/Logger.hpp"

static constexpr char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                  "0123456789";

RoomManager& RoomManager::get() {
    static RoomManager instance;
    return instance;
}

std::string RoomManager::generateUniqueCode() const {
    Logger::info("[RoomManager] Generating unique room code.");

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, sizeof(charset) - 2);

    while (true) {
        std::string code;

        for (size_t i = 0; i < 6; ++i) {
            code += charset[dist(rng)];
        }

        Logger::info("[RoomManager] Generated code: " + code);

        if (std::ranges::none_of(_rooms,
                                 [&code](const std::shared_ptr<Room>& room) {
                                     return room->getCode() == code;
                                 })) {
            Logger::info("[RoomManager] Code " + code + " is unique.");
            return code;
        }

        Logger::warning("[RoomManager] Code " + code +
                        " already exists. Retrying...");
    }
}

std::shared_ptr<Room>
RoomManager::createRoom(const std::shared_ptr<Player>& owner, size_t capacity,
                        bool isPublic) {
    Logger::info("[RoomManager] Creating a new room.");

    std::string code = generateUniqueCode();
    auto room = std::make_shared<Room>(code, owner, capacity, isPublic);

    _rooms.push_back(room);

    Logger::success("[RoomManager] Room created successfully with code: " +
                    code + ", Owner: " + owner->getName() +
                    ", Capacity: " + std::to_string(capacity) +
                    ", Public: " + (isPublic ? "true" : "false"));

    return room;
}

bool RoomManager::deleteRoom(const std::string& roomCode,
                             const std::shared_ptr<Player>& requester) {
    Logger::info("[RoomManager] Attempting to delete room with code: " +
                 roomCode);

    const auto it = std::ranges::find_if(
        _rooms, [&roomCode](const std::shared_ptr<Room>& room) {
            return room->getCode() == roomCode;
        });

    if (it != _rooms.end()) {
        if ((*it)->getOwner() == requester) {
            _rooms.erase(it);

            Logger::success("[RoomManager] Room with code " + roomCode +
                            " deleted successfully.");
            return true;
        }

        Logger::warning("[RoomManager] Unauthorized delete attempt by: " +
                        requester->getName());
        return false;
    }

    Logger::warning("[RoomManager] Room not found with code: " + roomCode);
    return false;
}

std::shared_ptr<Room>
RoomManager::findRoomByCode(const std::string& code) const {
    Logger::info("[RoomManager] Searching for room with code: " + code);

    for (const auto& room : _rooms) {
        if (room->getCode() == code) {
            Logger::info("[RoomManager] Room found with code: " + code);
            return room;
        }
    }

    Logger::warning("[RoomManager] Room not found with code: " + code);
    return nullptr;
}

const std::vector<std::shared_ptr<Room>>& RoomManager::getRooms() const {
    Logger::info("[RoomManager] Retrieving all rooms. Total rooms: " +
                 std::to_string(_rooms.size()));
    return _rooms;
}