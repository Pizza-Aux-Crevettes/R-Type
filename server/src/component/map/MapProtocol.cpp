/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** MapProtocol.cpp
*/

#include "component/map/MapProtocol.hpp"
#include "component/obstacle/ObstacleManager.hpp"
#include "protocol/Protocol.hpp"
#include "socket/UdpSocket.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"

/**
 * @brief Send a viewport update to a client
 *
 * @param clientAddr The client's address
 * @param smartBuffer The SmartBuffer to use for the response
 *
 * Protocol: UPDATE_VIEWPORT
 * Payload: viewport (double)
 */
void MapProtocol::sendViewportUpdate(const sockaddr_in& clientAddr,
                                     SmartBuffer& smartBuffer) {
    double viewport = ObstacleManager::get().getViewport();

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::UPDATE_VIEWPORT)
                << static_cast<double>(viewport);

    UdpSocket::get().sendToOne(clientAddr, smartBuffer);

    Logger::packet("[MapProtocol] Viewport update sent to client:\n"
                   " - Value: " +
                   std::to_string(viewport));
}

/**
 * @brief Send an obstacles update to a client
 *
 * @param clientAddr The client's address
 * @param smartBuffer The SmartBuffer to use for the response
 *
 * Protocol: UPDATE_OBSTACLES
 * Payload: id (int32_t), x (int32_t), y (int32_t), size (int16_t), type
 * (int16_t)
 */
void MapProtocol::sendObstaclesUpdate(const sockaddr_in& clientAddr,
                                      SmartBuffer& smartBuffer) {
    const auto& visibleObstacles = ObstacleManager::get().getVisibleObstacles();
    for (const auto& obstacle : visibleObstacles) {
        smartBuffer.reset();
        smartBuffer << static_cast<int16_t>(Protocol::OpCode::UPDATE_OBSTACLES)
                    << static_cast<int32_t>(obstacle->getId())
                    << static_cast<int32_t>(obstacle->getPosition().getX())
                    << static_cast<int32_t>(obstacle->getPosition().getY())
                    << static_cast<int16_t>(BLOCK_SIZE)
                    << static_cast<int16_t>(obstacle->getType());

        UdpSocket::get().sendToOne(clientAddr, smartBuffer);

        Logger::packet(
            "[MapProtocol] Obstacle update sent:\n"
            "  - ID: " +
            std::to_string(obstacle->getId()) + "\n  - Position: (" +
            std::to_string(obstacle->getPosition().getX()) + ", " +
            std::to_string(obstacle->getPosition().getY()) + ")" +
            "\n  - Type: " +
            ObstacleManager::get().ObstacleTypeToString(obstacle->getType()));
    }
}

/**
 * @brief Delete a entity and broadcast the deletion to all clients
 *
 * @param entityId The entity ID
 *
 * Protocol: DELETE_ENTITY
 * Payload: entityId (int32_t)
 */
void MapProtocol::sendEntityDeleted(const int32_t entityId) {
    SmartBuffer smartBuffer;
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::DELETE_ENTITY)
                << static_cast<int32_t>(entityId);

    UdpSocket::get().sendToAll(smartBuffer);

    Logger::packet("[PlayerProtocol] Entity deleted sent:\n"
                   "  - Entity ID: " +
                   std::to_string(entityId));
}
