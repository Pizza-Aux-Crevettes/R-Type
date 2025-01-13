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
 * @param smartBuffer The smart buffer
 *
 * Protocol: BULLET_POSITION_UPDATE
 * Payload: bulletId (int32_t), posX (int32_t), posY (int32_t)
 */
void BulletProtocol::sendBulletsUpdate(const sockaddr_in& clientAddr,
                                       SmartBuffer& smartBuffer) {
    auto& bullets = BulletManager::get().getBullets();
    for (const auto& [id, bullet] : bullets) {
        smartBuffer.reset();
        smartBuffer << static_cast<int16_t>(
                           Protocol::OpCode::BULLET_POSITION_UPDATE)
                    << static_cast<int32_t>(bullet->getId())
                    << static_cast<int32_t>(bullet->getPosition().getX())
                    << static_cast<int32_t>(bullet->getPosition().getY());

        UdpSocket::get().sendToOne(clientAddr, smartBuffer);

        Logger::packet("[BulletProtocol] Bullet update sent:\n"
                       "  - Bullet ID: " +
                       std::to_string(bullet->getId()) +
                       "\n"
                       "  - Position: (" +
                       std::to_string(bullet->getPosition().getX()) + ", " +
                       std::to_string(bullet->getPosition().getY()) + ")");
    }
}
