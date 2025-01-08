/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerProtocol.cpp
*/

#include "component/player/PlayerProtocol.hpp"
#include "component/player/PlayerManager.hpp"
#include "protocol/Protocol.hpp"
#include "socket/TcpSocket.hpp"
#include "socket/UdpSocket.hpp"
#include "util/Logger.hpp"

/**
 * Protocol Details:
 * - Input: std:string name
 * - Output: int16_t opCode (NEW_PLAYER_CALLBACK) << int32_t userId
 */
void PlayerProtocol::newPlayer(const int clientSocket, SmartBuffer& smartBuffer,
                               const sockaddr_in& clientAddr) {
    std::string name;

    smartBuffer >> name;
    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::NEW_PLAYER_CALLBACK);

    const auto player = PlayerManager::get().createPlayer(name);

    Logger::info("[PlayerProtocol] Assigned player ID " +
                 std::to_string(player->getId()) + " to client.");

    smartBuffer << player->getId();
    TcpSocket::sendToOne(clientSocket, smartBuffer);

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::NEW_PLAYER_BROADCAST);
    smartBuffer << player->getId() << std::string{player->getName()};
    TcpSocket::sendToAll(smartBuffer);
}

void PlayerProtocol::sendPlayerPositionUpdate(
    const int udpSocket, const std::vector<std::shared_ptr<Player>>& players,
    const std::shared_ptr<Player>& player, SmartBuffer& smartBuffer) {
    smartBuffer << static_cast<int16_t>(
                       Protocol::OpCode::PLAYER_UPDATE_POSITION)
                << player->getId() << player->getPosition().getX()
                << player->getPosition().getY();
    UdpSocket::send(udpSocket, player->getClientAddress(), smartBuffer);
    std::cout << "UpdatePosition: " << player->getPosition().getX() << ","
              << player->getPosition().getY() << std::endl;
}