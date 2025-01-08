/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** HotkeysManager.cpp
*/

#include "component/hotkey/HotkeysManager.hpp"
#include "protocol/Protocol.hpp"
#include "socket/UdpSocket.hpp"
#include "util/Logger.hpp"

#include <SmartBuffer.hpp>
#include <iostream>

HotkeysManager::HotkeysManager() {
    _keys = {{HotkeysCodes::ARROW_TOP, sf::Keyboard::Up},
             {HotkeysCodes::ARROW_BOTTOM, sf::Keyboard::Down},
             {HotkeysCodes::ARROW_LEFT, sf::Keyboard::Left},
             {HotkeysCodes::ARROW_RIGHT, sf::Keyboard::Right}};
}

HotkeysManager::~HotkeysManager() = default;

sf::Keyboard::Key HotkeysManager::getKey(const HotkeysCodes hotkey) {
    return _keys[hotkey];
}

void HotkeysManager::setKey(const HotkeysCodes hotkey,
                            sf::Keyboard::Key newKey) {
    _keys[hotkey] = newKey;
}

void HotkeysManager::checkKey(const sf::Event& event) {
    for (const auto& [hotkey, key] : _keys) {
        if (key == event.key.code) {
            SmartBuffer smartBuffer;
            Logger::debug(std::to_string(event.key.code));
            smartBuffer << static_cast<int16_t>(
                               Protocol::OpCode::HOTKEY_PRESSED)
                        << 1 << static_cast<int16_t>(hotkey);
            UdpSocket::send(smartBuffer);
        }
    }
}
