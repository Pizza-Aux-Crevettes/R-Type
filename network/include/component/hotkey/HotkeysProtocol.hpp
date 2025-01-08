/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** HotkeysProtocol.hpp
*/

#pragma once
#include <memory>
#include "SmartBuffer.hpp"
#include "socket/client/Client.hpp"

class HotkeysProtocol {
  public:
    static void processHotkey(std::shared_ptr<Client> client,
                              SmartBuffer& smartBuffer);
};
