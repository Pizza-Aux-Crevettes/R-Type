/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** main.cpp
*/

#include "Entity.hpp"

#include <components/Bullet.hpp>
#include <components/Button.hpp>

int main(int ac, char* av[]) {
    GameEngine::Entity player;
    player.addComponent(Button("Player", {0.0 + 1.0, 0.0}));
    player.addComponent(Bullet(10));
    player.displayComponents();
    player.removeComponent<Button>();
    player.displayComponents();
    return 0;
}
