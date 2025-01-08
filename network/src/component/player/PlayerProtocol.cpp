/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** PlayerProtocol.cpp
*/

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

void PlayerProtocol::newPlayer(std::shared_ptr<Client> client,
                               SmartBuffer& smartBuffer) {
    std::string name;

    smartBuffer >> name;

    auto player = PlayerManager::get().createPlayer(name);
    client->setPlayer(player);

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::NEW_PLAYER_CALLBACK)
                << player->getId();
    TcpSocket::sendToOne(client->getTcpSocket(), smartBuffer);

    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(Protocol::OpCode::NEW_PLAYER_BROADCAST)
                << player->getId() << name;
    TcpSocket::sendToAll(smartBuffer);
}

void PlayerProtocol::sendPlayerPositionUpdate(
    int udpSocket, const std::vector<std::shared_ptr<Player>>& players,
    const std::shared_ptr<Player>& player, SmartBuffer& smartBuffer) {
    smartBuffer.reset();
    smartBuffer << static_cast<int16_t>(
                       Protocol::OpCode::PLAYER_UPDATE_POSITION)
                << player->getId() << player->getPosition().getX()
                << player->getPosition().getY();

    for (auto& p : players) {
        UdpSocket::send(udpSocket, p->getClientAddress(), smartBuffer);
    }
}