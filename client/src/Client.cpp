/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** This file declares the `Client` class, responsible for managing the
** client's entities and items in the game context. It allows for the
** creation, updating, and drawing of items as well as setting their
** properties like position, text, and sprites.
** Client.cpp
*/

#include "Client.hpp"


void runNetworkClient(NetworkClient& networkClient) {
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

Client::Client() {}

Client::~Client() {}

void Client::manageBackground(GameEngine::System system, sf::Clock clock,
                              sf::Texture background) {

    sf::Vector2f textureOffset(0.f, 0.f);
    const float scrollSpeed = 100.f;
    std::lock_guard<std::mutex> guard(EntityManager::get().getMutex());
    std::map<int, GameEngine::Entity> entityList = EntityManager::get().getEntityList();

    sf::Time elapsed = clock.restart();
    textureOffset.x += scrollSpeed * elapsed.asSeconds();
    textureOffset.x = Client::get().getViewport();
    sf::RectangleShape& shape =
        entityList.at(0).getComponent<Shape>().getRect();
    shape.setTextureRect(
        sf::IntRect(textureOffset.x, textureOffset.y, 800, 600));
}

void Client::manageSound() {
    SoundManager::get().setMusicSound("menu", "assets/sounds/ambien-song.wav");
    SoundManager::get().setMusicSound("game", "assets/sounds/boss-song.wav");
    SoundManager::get().setEffectSound("bullet", "assets/sounds/shoot-sound.wav");
    SoundManager::get().setEffectSound("click", "assets/sounds/click-menu.wav");

    SoundManager::get().setEffectSound("click", "assets/sounds/click-menu.wav");
    SoundManager::get().setEffectSound("click", "assets/sounds/click-menu.wav");
    SoundManager::get().getMusicSound("menu").getSound().play();
}

void Client::processEvents(sf::RenderWindow& window, GameEngine::System& system, 
                           OptionMenu& optionMenu, bool serverInitialized) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            SoundManager::get().getEffectSound("click").getSound().play();
        }
        if (serverInitialized) {
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == HotkeysManager::get().getKey(HotkeysCodes::SPACE)) {
                SoundManager::get().getEffectSound("bullet").getSound().play();
            }
        }
        if (event.type == sf::Event::KeyPressed) {
            HotkeysManager::get().checkKey(event);
        }
        Menu::get().setupInput(event);
        optionMenu.setNewKey(event, system);
    }
}

void Client::handleAutoFire(sf::Clock& clock) {
    if (HotkeysManager::get().getAutoFireState() &&
        clock.getElapsedTime().asSeconds() >= 0.30f) {
        SmartBuffer smartBuffer;
        smartBuffer << static_cast<int16_t>(Protocol::OpCode::HOTKEY_PRESSED)
                    << static_cast<int32_t>(Protocol::get().getPlayerId())
                    << static_cast<int16_t>(HotkeysCodes::SPACE);
        UdpSocket::send(smartBuffer);
        clock.restart();
    }
}

void Client::initializeServer(bool& serverInitialized, std::unique_ptr<NetworkClient>& networkClient, 
                              std::thread& serverThread, sf::RenderWindow& window) {
    try {
        std::string ipAdress = Client::get().getIp().empty() ? "127.0.0.1" : Client::get().getIp();
        std::string username = Client::get().getUsername().empty() ? "Guest" : Client::get().getUsername();

        std::cout << ipAdress << std::endl;
        std::cout << username << std::endl;
        Client::get().setIp(ipAdress);
        Client::get().setUsername(username);

        networkClient = std::make_unique<NetworkClient>(ipAdress, SERVER_PORT);
        initializeNetwork(*networkClient);

        serverThread = std::thread(runNetworkClient, std::ref(*networkClient));
        serverThread.detach();

        SmartBuffer smartBuffer;
        smartBuffer << static_cast<int16_t>(Protocol::OpCode::CREATE_PLAYER);
        smartBuffer << username;
        TcpSocket::send(smartBuffer);

        SoundManager::get().getMusicSound("menu").getSound().stop();
        SoundManager::get().getMusicSound("game").getSound().play();
        serverInitialized = true;
    } catch (const std::exception& e) {
        Logger::error("[Main] Failed to initialize network: " + std::string(e.what()));
        window.close();
    }
}

void Client::updateGameState(sf::RenderWindow& window, GameEngine::System& system, 
                             LifeBar& lifeBarMenu) {
    std::lock_guard<std::mutex> guard(EntityManager::get().getMutex());
    std::map<int, GameEngine::Entity> entitiesList = EntityManager::get().getEntityList();
    if (!entitiesList.empty()) {
        setDisplayEntity(entitiesList);
        system.render(window, _displayEntities);
    }
    lifeBarMenu.displayLifeBar(window, system);
}

void Client::manageClient() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "RTYPE");
    GameEngine::System system;
    sf::Texture background = EntityManager::get().manageBackground(window);
    OptionMenu optionMenu;
    LifeBar lifeBarMenu;
    LoseMenu loseMenu;
    sf::Clock clock;
    bool serverInitialized = false;
    std::unique_ptr<NetworkClient> networkClient = nullptr;
    std::thread serverThread;

    manageSound();

    while (window.isOpen()) {
        manageBackground(system, clock, background);
        processEvents(window, system, optionMenu, serverInitialized);
        handleAutoFire(clock);

        window.clear();

        if (!Client::get().getIsPlayed()) {
            Menu::get().displayMenu(window, system, optionMenu);
        } else {
            if (!serverInitialized) {
                initializeServer(serverInitialized, networkClient, serverThread, window);
            }
            updateGameState(window, system, lifeBarMenu);
        }

        window.display();
    }

    if (serverThread.joinable()) {
        serverThread.join();
    }
}

void Client::setUsername(std::string username) {
    _username = username;
}
void Client::setPort(std::string port) {
    _port = port;
}
void Client::setIp(std::string Ip) {
    _ip = Ip;
}
std::string Client::getUsername() {
    return _username;
}
std::string Client::getPort() {
    return _port;
}
std::string Client::getIp() {
    return _ip;
}

sf::Event Client::getEvent() {
    return _event;
}

void Client::setViewport(double viewport) {
    _viewportX = viewport;
}

double Client::getViewport() {
    return _viewportX;
}

void Client::setDisplayEntity(std::map<int, GameEngine::Entity> entities) {
    _displayEntities.clear();
    for (const auto& [id, entity] : entities) {
        _displayEntities.emplace(id, entity);
    }
}

Client& Client::get() {
    static Client instance;
    return instance;
}

void Client::setIsPlayed() {
    _isPlay = !_isPlay;
}

bool Client::getIsPlayed() {
    return _isPlay;
}
