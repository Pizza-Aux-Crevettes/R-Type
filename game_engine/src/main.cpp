/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** main.cpp
*/

#include "Entity.hpp"
#include <components/Bullet.hpp>
#include <components/Button.hpp>
#include <components/Health.hpp>
#include <components/Velocity.hpp>
#include <iostream>

int main(int ac, char* av[]) {
    try {
        GameEngine::Entity player(Health(30), Velocity());
        player.displayComponents();
        std::cout << "-----" << std::endl;
        player.addComponent(Button("Player", {0.0 + 1.0, 0.0}));
        player.addComponent(Bullet(10));
        player.displayComponents();
        std::cout << "-----" << std::endl;
        player.removeComponent<Bullet>();
        player.displayComponents();
        player.removeComponent<Button>();
        player.removeComponent<Bullet>();
        std::cout << "-----" << std::endl;
        player.displayComponents();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
