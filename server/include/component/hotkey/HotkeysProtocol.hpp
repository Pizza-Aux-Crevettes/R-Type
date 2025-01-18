/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** HotkeysProtocol.hpp
*/

#pragma once

#include <netinet/in.h>
#include <SmartBuffer.hpp>

class HotkeysProtocol {
  public:
    static void processHotkey(int clientSocket, SmartBuffer& smartBuffer, const sockaddr_in& clientAddr);
};
