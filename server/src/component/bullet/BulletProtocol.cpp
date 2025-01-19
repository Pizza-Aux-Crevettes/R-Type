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
 * @param clientAddr The client address
 * @param smartBuffer The smart buffer
 *
 * Protocol: UPDATE_BULLETS
 * Payload: bulletId (int32_t), posX (int32_t), posY (int32_t)
 */
void BulletProtocol::sendBulletsUpdate(const sockaddr_in& clientAddr,
                                       SmartBuffer& smartBuffer) {
    auto bullets = BulletManager::get().getBullets();
    for (const auto& bullet : bullets) {
        smartBuffer.reset();
        smartBuffer << static_cast<int16_t>(Protocol::OpCode::UPDATE_BULLETS)
                    << static_cast<int32_t>(bullet->getId())
                    << static_cast<int32_t>(bullet->getPosition().getX())
                    << static_cast<int32_t>(bullet->getPosition().getY())
                    << static_cast<int16_t>(bullet->getType());

        UdpSocket::get().sendToOne(clientAddr, smartBuffer);
    }
}
