/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** This file declares the Client class, responsible for managing the
** client's entities and items in the game context. It allows for the
** creation, updating, and drawing of items as well as setting their
** properties like position, text, and sprites.
** Client.cpp
*/

#include "Client.hpp"

Client::Client() {}

Client::~Client() {}

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
void Client::saveScoreToFile(int score, int kills) {
    std::ofstream file("score.txt", std::ios::app);
    if (file.is_open()) {
        file << "----------------------" << std::endl;
        file << "Username: " << Client::get().getUsername() << std::endl;
        file << "Score: " << score << std::endl;
        file << "Kills: " << kills << std::endl;
        file.close();
        std::cout << "Score added in score.txt" << std::endl;
    } else {
        std::cerr << "Error: Unable to open the file for saving." << std::endl;
    }
}

void Client::getBestScore() {
    std::ifstream file("score.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open the file score.txt." << std::endl;
        return;
    }

    std::string line, bestUsername, currentUsername;
    int bestKills = 0, bestScore = 0;
    int currentKills = -1, currentScore = -1;

    while (std::getline(file, line)) {
        if (line.find("Username: ") != std::string::npos) {
            currentUsername = line.substr(10);
        } else if (line.find("Kills: ") != std::string::npos) {
            currentKills = std::stoi(line.substr(7));
        } else if (line.find("Score: ") != std::string::npos) {
            currentScore = std::stoi(line.substr(7));
        }

        if (!currentUsername.empty() && currentKills != -1 && currentScore != -1) {
            if (currentKills > bestKills || (currentKills == bestKills && currentScore > bestScore)) {
                bestKills = currentKills;
                bestScore = currentScore;
                bestUsername = currentUsername;
            }

            currentUsername = "";
            currentKills = -1;
            currentScore = -1;
        }
    }

    file.close();

    if (!bestUsername.empty()) {
        Client::get().setBestKills(bestKills);
        Client::get().setBestScore(bestScore);
        Client::get().setBestUsername(bestUsername);
    } else {
        std::cout << "Aucun score enregistré." << std::endl;
    }
}

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
    SoundManager::get().setMusicSound("lose", "assets/sounds/lose.wav");
    SoundManager::get().setMusicSound("win", "assets/sounds/win.wav");

    SoundManager::get().setEffectSound("click", "assets/sounds/click-menu.wav");
    SoundManager::get().setEffectSound("click", "assets/sounds/click-menu.wav");
    SoundManager::get().getMusicSound("menu").getSound().play();
}

void Client::processEvents(sf::RenderWindow& window, GameEngine::System& system, bool serverInitialized) {
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
        OptionMenu::get().setNewKey(event, system);
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
                             LifeBar& lifeBarMenu, BossLifeBar& bossLifeBarMenu) {
    std::lock_guard<std::mutex> guard(EntityManager::get().getMutex());
    std::map<int, GameEngine::Entity> entitiesList = EntityManager::get().getEntityList();
    if (!entitiesList.empty()) {
        setDisplayEntity(entitiesList);
        system.render(window, _displayEntities);
    }
    lifeBarMenu.displayLifeBar(window, system);
    bossLifeBarMenu.displayBossLifeBar(window, system);
}

void Client::manageClient() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "RTYPE");
    GameEngine::System system;
    sf::Texture background = EntityManager::get().manageBackground(window);
    OptionMenu optionMenu;
    LifeBar lifeBarMenu;
    BossLifeBar bossLifeBar;
    sf::Clock clock;
    bool serverInitialized = false;
    std::unique_ptr<NetworkClient> networkClient = nullptr;
    std::thread serverThread;

    manageSound();
    getBestScore();

    while (window.isOpen()) {
        manageBackground(system, clock, background);
        processEvents(window, system, serverInitialized);
        handleAutoFire(clock);

        window.clear();

        if (!Client::get().getIsPlayed()) {
            Menu::get().displayMenu(window, system);
        } else if (Client::get().getIsWinGame()) {
            WinMenu::get().displayWnMenu(window, system);
        }  else if (Client::get().getIsLoseGame()) {
            LoseMenu::get().displayLoseMenu(window, system);
        } else {
            if (!serverInitialized) {
                initializeServer(serverInitialized, networkClient, serverThread, window);
            }
            updateGameState(window, system, lifeBarMenu, bossLifeBar);
        }

        window.display();
    }

    saveScoreToFile(Client::get().getScore(), Client::get().getKills());

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

void Client::setIsWinGame() {
    _isWin = true;
}

bool Client::getIsWinGame() {
    return _isWin;
}

void Client::setIsLoseGame() {
    _isLose = true;
}

bool Client::getIsLoseGame() {
    return _isLose;
}

void Client::setScore(int score) {
    _score = score;
}

int Client::getScore() {
    return _score;
}

void Client::setKills(int kills) {
    _kills = kills;
}

int Client::getKills() {
    return _kills;
}

void Client::setBestScore(int bestScore) {
    _bestScore = bestScore;
}

int Client::getBestScores() {
    return _bestScore;
}
void Client::setBestKills(int bestKills) {
    _bestKills = bestKills;
}

int Client::getBestKills() {
    return _bestKills;
}

void Client::setBestUsername(std::string bestUsername) {
    _bestUsername = bestUsername;
}

std::string Client::getBestUsername() {
    return _bestUsername;
}
