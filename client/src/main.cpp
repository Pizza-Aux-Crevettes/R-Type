/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** main.cpp
*/

#include <SFML/Audio.hpp>
#include <thread>
#include "System.hpp"
#include "components/Position.hpp"
#include "components/Sprite.hpp"
#include "components/Text.hpp"
#include "components/Texture.hpp"
#include "protocol/NetworkClient.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"

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

static void initMainMenu(std::map<int, GameEngine::Entity>& entities) {
    float totalButtonHeight = 3;
    float verticalSpacing = (1080 - totalButtonHeight) / (3 + 2);

    auto map = GameEngine::Entity(1, Sprite({8, 8}),
                                  Texture("../../assets/sprite/map.png"),
                                  Position({{-1300, -300}}));
    auto buttonPlay = GameEngine::Entity(
        2, Button("PLAY", "../../assets/font/Inter_Bold.ttf", 50),
        Position({{1920 / 2 - 60, (verticalSpacing + 130)}}));
    auto buttonOption = GameEngine::Entity(
        3, Button("OPTION", "../../assets/font/Inter_Bold.ttf", 50),
        Position({{1920 / 2 - 100, verticalSpacing * 2 + 50}}));
    auto buttonExit = GameEngine::Entity(
        4, Button("EXIT", "../../assets/font/Inter_Bold.ttf", 50),
        Position({{1920 / 2 - 50, verticalSpacing * 3 - 20}}));
    auto spaceShip = GameEngine::Entity(
        5, Sprite({6, 6}),
        Texture("../../assets/sprite/spaceship.png", {0, 18, 34, 15}),
        Position({{30, 100}}));
    auto shootBlue = GameEngine::Entity(
        6, Sprite({5, 5}),
        Texture("../../assets/sprite/shoot_blue.png", {165, 0, 65, 15}),
        Position({{350, 100}}));
    auto enemy = GameEngine::Entity(
        7, Sprite({5, 5}),
        Texture("../../assets/sprite/enemy.png", {0, 0, 50, 80}),
        Position({{280, 820}}));
    auto canonUp = GameEngine::Entity(
        8, Sprite({5, 5}),
        Texture("../../assets/sprite/canon.png", {165, 0, 33, 30}),
        Position({{1600, -50}}));
    auto canonDown = GameEngine::Entity(
        9, Sprite({5, 5}),
        Texture("../../assets/sprite/canon.png", {33, 33, 33, 30}),
        Position({{1600, 970}}));
    auto boss = GameEngine::Entity(
        10, Sprite({3, 3}),
        Texture("../../assets/sprite/intact-boss.png", {0, 0, 200, 200}),
        Position({{1400, 200}}));
    entities.emplace(1, std::move(map));
    entities.emplace(2, std::move(buttonPlay));
    entities.emplace(3, std::move(buttonOption));
    entities.emplace(4, std::move(buttonExit));
    entities.emplace(5, std::move(spaceShip));
    entities.emplace(6, std::move(shootBlue));
    entities.emplace(7, std::move(enemy));
    entities.emplace(8, std::move(canonUp));
    entities.emplace(9, std::move(canonDown));
    entities.emplace(10, std::move(boss));
}

static void initLifeBar(std::map<int, GameEngine::Entity>& entities) {
    auto rocket = GameEngine::Entity(
        11, Sprite({1, 1}),
        Texture("../../assets/sprite/rocket.png", {0, 0, 100, 200}),
        Position({{150, 930}}));
    auto numberLife = GameEngine::Entity(
        12, Text("3", "../../assets/font/Inter_Bold.ttf", 60),
        Position({{250, 950}}));
    entities.emplace(11, std::move(rocket));
    entities.emplace(12, std::move(numberLife));
}

static void game() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Client Game");
    std::map<int, GameEngine::Entity> entities;

    sf::SoundBuffer ambienBuffer;
    sf::SoundBuffer clickBuffer;

    if (!ambienBuffer.loadFromFile("../../assets/sounds/ambien-song.wav")) {
        std::cerr << "Error: unable to load the audio file." << std::endl;
        Logger::error("[GAME] Error: can't play sound");
    }

    if (!clickBuffer.loadFromFile("../../assets/sounds/click-menu.wav")) {
        std::cerr << "Error: unable to load the audio file." << std::endl;
        Logger::error("[GAME] Error: can't play sound");
    }

    sf::Sound ambienSound;
    sf::Sound clickMenuSound;

    ambienSound.setBuffer(ambienBuffer);
    clickMenuSound.setBuffer(clickBuffer);

    ambienSound.play();

    initMainMenu(entities);
    // initLifeBar(entities);

    GameEngine::System system;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    clickMenuSound.play();
                    system.onClick(window, entities, mousePos);
                }
            }
        }
        window.clear();
        system.render(window, entities);
        window.display();
    }
}

int main() {
    try {

        game();

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
