/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** RoomManager.hpp
*/

#pragma once

#include "component/room/Room.hpp"
#include <string>
#include <vector>

class RoomManager {
  public:
    RoomManager(const RoomManager&) = delete;
    RoomManager& operator=(const RoomManager&) = delete;

    static RoomManager& getInstance();

    std::shared_ptr<Room> createRoom(const std::shared_ptr<Player>& owner,
                                     size_t capacity, bool isPublic);
    bool deleteRoom(const std::string& roomCode,
                    const std::shared_ptr<Player>& requester);
    [[nodiscard]] std::shared_ptr<Room>
    findRoomByCode(const std::string& code) const;
    [[nodiscard]] const std::vector<std::shared_ptr<Room>>& getRooms() const;

  private:
    RoomManager();
    ~RoomManager();

    [[nodiscard]] std::string generateUniqueCode() const;

    std::vector<std::shared_ptr<Room>> _rooms;
};
