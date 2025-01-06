/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** main.cpp
*/

#include <thread>
#include "protocol/NetworkClient.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"
#include <System.hpp>
#include <components/Text.hpp>
#include <components/Link.hpp>
#include <components/Position.hpp>
#include <components/Sprite.hpp>
#include <components/Shape.hpp>
#include <components/Color.hpp>

void runNetworkClient(NetworkClient& networkClient, Client* client) {
    try {
        networkClient.run();
    } catch (const std::exception& e) {
        Logger::error("[Server Thread] Error: " + std::string(e.what()));
    }
}

void initializeNetwork(NetworkClient& networkClient) {
    networkClient.init();
    networkClient.connectTCP();
    networkClient.connectUDP();

    Logger::success("[Main] Network initialized successfully.");
}

/*
int main() {
    try {
        Client client;
        NetworkClient networkClient("127.0.0.1", SERVER_PORT);

        initializeNetwork(networkClient);
        std::thread serverThread(runNetworkClient, std::ref(networkClient),
                                 &client);
        client.manageClient();

        if (serverThread.joinable()) {
            serverThread.join();
        }
    } catch (const std::exception& e) {
        Logger::error("[Main] Error: " + std::string(e.what()));

        return FAILURE;
    }

    return SUCCESS;
}
*/


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Client Game");
    std::map<int, GameEngine::Entity> entities;
    auto player = GameEngine::Entity(0, Sprite(), Texture("../../assets/sprite/spaceship.png", {0, 0, 34, 15}), Position({{0, 0}}));
    auto player2 = GameEngine::Entity(2, Text("Nakimee", "../../assets/font/arial.ttf", 10), Position({{0, -14}, {100, 100}, {400, 400}}), Link(1));
    auto test = GameEngine::Entity(3, Shape(Circle, {100, 100}, 100), Position({{0, 0}}), Color({255, 0, 0, 255}));
    entities.emplace(1, std::move(player));
    entities.emplace(2, std::move(player2));
    entities.emplace(3, std::move(test));
    GameEngine::System system;
    float x, y = 0.0f;
    float deltaTime = 0.0f;
    float speed = 200.0f;
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        deltaTime = clock.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            y -= speed * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            y += speed * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            x -= speed * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            x += speed * deltaTime;
        }
        system.update(1, entities, GameEngine::UpdateType::Position, std::pair(x, y));
        window.clear();
        system.render(window, entities);
        window.display();
    }
    return 0;
}
