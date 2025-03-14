/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** EnemyProtocol.cpp
*/

#include "component/enemy/EnemyProtocol.hpp"
#include "component/enemy/EnemyManager.hpp"
#include "protocol/Protocol.hpp"
#include "socket/UdpSocket.hpp"
#include "util/Config.hpp"

/**
 * @brief Send an enemies update to a client
 *
 * @param clientAddr The client's address
 * @param smartBuffer The SmartBuffer to use for the response
 *
 * Protocol: UPDATE_ENEMIES
 * Payload: id (int32_t), x (int32_t), y (int32_t), width (int16_t), height
 * (int16_t), type (int16_t)
 */
void EnemyProtocol::sendEnemiesUpdate(const sockaddr_in& clientAddr,
                                      SmartBuffer& smartBuffer) {
    const auto& visibleEnemies = EnemyManager::get().getVisibleEnemies();
    for (const auto& enemy : visibleEnemies) {
        if (enemy->isAlive()) {
            smartBuffer.reset();
            smartBuffer << static_cast<int16_t>(
                               Protocol::OpCode::UPDATE_ENEMIES)
                        << static_cast<int32_t>(enemy->getId())
                        << static_cast<int32_t>(enemy->getPosition().getX())
                        << static_cast<int32_t>(enemy->getPosition().getY())
                        << static_cast<int16_t>(enemy->getWidth())
                        << static_cast<int16_t>(enemy->getHeight())
                        << static_cast<int16_t>(enemy->getType());

            UdpSocket::get().sendToOne(clientAddr, smartBuffer);
        }
    }
}
