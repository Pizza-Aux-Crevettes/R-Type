/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** EnemyManager.cpp
*/

#include "component/enemy/EnemyManager.hpp"
#include "component/bullet/BulletManager.hpp"
#include "component/map/MapProtocol.hpp"
#include "component/player/PlayerManager.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"

/**
 * @brief Construct a new EnemyManager:: Enemy Manager object
 *
 */
EnemyManager& EnemyManager::get() {
    static EnemyManager instance;
    return instance;
}

/**
 * @brief Construct a new EnemyManager:: Enemy Manager object
 *
 */
EnemyManager::EnemyManager() {
    _enemyMapping = {
        {"E001", {EnemyType::ENEMY1, 3, 40, 40, 5, 1000, 300}},
        {"E002", {EnemyType::ENEMY2, 10, 50, 50, 4, 800, 400}},
        {"E003", {EnemyType::ENEMY3, 1, 60, 60, 6, 1200, 350}},
        {"E004", {EnemyType::ENEMY4, 7, 70, 70, 7, 900, 250}},
    };

    Logger::success("[EnemyManager] Initialized enemy mappings.");
}

/**
 * @brief Destroy the EnemyManager:: Enemy Manager object
 *
 */
EnemyManager::~EnemyManager() {
    _enemies.clear();
    _visibleEnemies.clear();
}

/**
 * @brief Convert an EnemyType to a string
 *
 * @param type The EnemyType
 * @return std::string The string representation
 */
std::string EnemyManager::EnemyTypeToString(EnemyType type) const {
    switch (type) {
    case EnemyType::NONE:
        return "NONE";
    case EnemyType::ENEMY1:
        return "ENEMY1";
    case EnemyType::ENEMY2:
        return "ENEMY2";
    case EnemyType::ENEMY3:
        return "ENEMY3";
    case EnemyType::ENEMY4:
        return "ENEMY4";
    default:
        return "UNKNOWN";
    }
}

/**
 * @brief Get the properties of an enemy by its code
 *
 * @param code The enemy code
 * @return EnemyProperties The properties of the enemy
 */
EnemyProperties
EnemyManager::getEnemyProperties(const std::string& code) const {
    auto it = _enemyMapping.find(code);
    if (it != _enemyMapping.end()) {
        return it->second;
    }

    throw std::runtime_error("[EnemyManager] Invalid enemy code: " + code);
}

/**
 * @brief Add an enemy to the manager
 *
 * @param enemy The enemy to add
 */
void EnemyManager::addEnemy(const std::shared_ptr<Enemy>& enemy) {
    _enemies.push_back(enemy);
}

/**
 * @brief Find an enemy by its ID
 *
 * @param enemyId The ID of the enemy
 * @return std::shared_ptr<Enemy> The enemy
 */
std::shared_ptr<Enemy> EnemyManager::findById(int enemyId) const {
    auto it = std::find_if(_enemies.begin(), _enemies.end(),
                           [enemyId](const std::shared_ptr<Enemy>& enemy) {
                               return enemy->getId() == enemyId;
                           });
    if (it != _enemies.end()) {
        return *it;
    }

    Logger::warning("[EnemyManager] Enemy not found. Enemy ID: " +
                    std::to_string(enemyId));
    return nullptr;
}

/**
 * @brief Update all enemies
 *
 */
void EnemyManager::updateEnemies() {
    _visibleEnemies.clear();

    for (auto it = _enemies.begin(); it != _enemies.end();) {
        auto& enemy = *it;
        enemy->move();

        if (enemy->getPosition().getX() < -enemy->getWidth()) {
            MapProtocol::sendEntityDeleted(enemy->getId());
            it = _enemies.erase(it);
        } else {
            if (enemy->getPosition().getX() < RENDER_DISTANCE * OBSTACLE_SIZE &&
                enemy->getPosition().getX() > -OBSTACLE_SIZE) {
                _visibleEnemies.push_back(enemy);
            }
            ++it;
        }
    }

    auto& players = PlayerManager::get().getPlayers();
    for (const auto& enemy : _visibleEnemies) {
        enemy->updateShootCooldown();
        if (!enemy->canShoot()) continue;

        for (const auto& player : players) {
            if (std::abs(player->getPosition().getX() -
                         enemy->getPosition().getX()) <
                enemy->getShootRange()) {
                BulletManager::get().handleEnemyShoot(enemy->getId());
                enemy->resetShootCooldown();
                break;
            }
        }
    }
}

/**
 * @brief Get all enemies
 *
 * @return const std::vector<std::shared_ptr<Enemy>>&
 */
const std::vector<std::shared_ptr<Enemy>>& EnemyManager::getEnemies() const {
    return _enemies;
}

/**
 * @brief Get all visible enemies
 *
 * @return const std::vector<std::shared_ptr<Enemy>>&
 */
const std::vector<std::shared_ptr<Enemy>>&
EnemyManager::getVisibleEnemies() const {
    return _visibleEnemies;
}

/**
 * @brief Check if an enemy code is valid
 *
 * @param code The enemy code
 * @return bool
 */
bool EnemyManager::isEnemyCodeValid(const std::string& code) const {
    return _enemyMapping.find(code) != _enemyMapping.end();
}
