/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** BulletProtocol.cpp
*/

#include "component/bullet/BulletProtocol.hpp"
#include "component/bullet/BulletManager.hpp"
#include "protocol/Protocol.hpp"
#include "socket/UdpSocket.hpp"
#include "util/Logger.hpp"

/**
 * @brief Send the bullet update to the client
 *
 * @param udpSocket The UDP socket
 * @param client The client address
 * @param player The player
 * @param smartBuffer The smart buffer
 */
void sendBulletsUpdate(const int udpSocket, const sockaddr_in& client,
                       const std::shared_ptr<Player>& player,
                       SmartBuffer& smartBuffer) {
    // Get all bullets
    auto& bullets = BulletManager::get().getBullets();

    // Loop through all bullets
    for (const auto& [id, bullet] : bullets) {
        // Create the response buffer for the bullet
        smartBuffer.reset();
        smartBuffer << static_cast<int16_t>(
                           Protocol::OpCode::BULLET_POSITION_UPDATE)
                    << static_cast<int32_t>(bullet->getId())
                    << static_cast<int32_t>(bullet->getPosition().getX())
                    << static_cast<int32_t>(bullet->getPosition().getY());

        // Broadcast the bullet update to all clients
        UdpSocket::sendToOne(udpSocket, client, smartBuffer);

        Logger::packet("[BulletProtocol] Bullet update sent:\n"
                       "  - Bullet ID: " +
                       std::to_string(bullet->getId()) +
                       "\n"
                       "  - Position: (" +
                       std::to_string(bullet->getPosition().getX()) + ", " +
                       std::to_string(bullet->getPosition().getY()) + ")");
    }
}
