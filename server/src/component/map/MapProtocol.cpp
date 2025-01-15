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
}
