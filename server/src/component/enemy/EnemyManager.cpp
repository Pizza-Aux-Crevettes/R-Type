/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** EnemyManager.cpp
*/

#include "component/enemy/EnemyManager.hpp"
#include "component/bullet/BulletManager.hpp"
#include "component/map/MapProtocol.hpp"
#include "component/obstacle/ObstacleManager.hpp"
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
        {"E001",
         {
             EnemyType::GRUNT, // type
             1,                // speed
             50,               // width
             50,               // height
             2.5,              // bulletSpeed
             5,                // bulletDamage
             1600,             // shootCooldown
             500,              // shootRange
             100               // health
         }},
        {"E002", {EnemyType::SNIPER, 1, 40, 40, 1, 20, 3000, 800, 1000}},
        {"E003", {EnemyType::TANK, 0.5, 100, 100, 1, 15, 4000, 300, 1000}},
        {"E004", {EnemyType::SWARMER, 2.5, 30, 30, 2, 3, 800, 200, 2000}},
        {"E005", {EnemyType::BOSS, 0.5, 200, 200, 3.5, 50, 6000, 1000, 1000}},
        {"E006", {EnemyType::DRONE, 2, 40, 40, 24, 4, 1000, 1200, 1000}},
        {"E007", {EnemyType::MINION, 3, 20, 20, 4, 1, 300, 300, 1000}},
        {"E008", {EnemyType::CANNON, 0, 80, 80, 0.5, 25, 4000, 1000, 1000}}};

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
    case EnemyType::GRUNT:
        return "GRUNT";
    case EnemyType::SNIPER:
        return "SNIPER";
    case EnemyType::TANK:
        return "TANK";
    case EnemyType::SWARMER:
        return "SWARMER";
    case EnemyType::BOSS:
        return "BOSS";
    case EnemyType::DRONE:
        return "DRONE";
    case EnemyType::MINION:
        return "MINION";
    case EnemyType::CANNON:
        return "CANNON";
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
    prepare();

    for (const auto& enemy : _enemies) {
        if (ObstacleManager::get().getViewport() <
            ObstacleManager::get().getMaxViewport()) {
            enemy->move();
        }
        enemy->updateShootCooldown();
        forPlayers(enemy);
        invalidate(enemy);
    }
}

/**
 * @brief Prepare the manager for the next update
 *
 */
void EnemyManager::prepare() {
    _visibleEnemies.clear();

    if (!_enemiesToDelete.empty()) {
        for (const auto& enemyId : _enemiesToDelete) {
            removeEnemy(enemyId);
        }
        _enemiesToDelete.clear();
    }
}

/**
 * @brief Update the enemies for all players
 *
 */
void EnemyManager::forPlayers(const std::shared_ptr<Enemy>& enemy) {
    for (const auto& player : PlayerManager::get().getPlayers()) {
        if (enemy->collidesWith(player)) {
            PlayerManager::get().movePlayer(player->getId(), -enemy->getSpeed(),
                                            0);
            player->takeDamage(enemy->getBulletDamage() / 10);
        }

        if ((std::abs(player->getPosition().getX() -
                      enemy->getPosition().getX()) <= enemy->getShootRange()) &&
            (std::abs(player->getPosition().getY() -
                      enemy->getPosition().getY()) <= enemy->getShootRange()) &&
            enemy->canShoot()) {
            Point direction(
                player->getPosition().getX() - enemy->getPosition().getX(),
                player->getPosition().getY() - enemy->getPosition().getY());
            direction.normalize();
            BulletManager::get().handleEnemyShoot(enemy->getId(), direction);
            enemy->resetShootCooldown();
        }
    }
}

/**
 * @brief Invalidate an enemy
 *
 * @param enemy The enemy to invalidate
 */
void EnemyManager::invalidate(const std::shared_ptr<Enemy>& enemy) {
    if (enemy->getPosition().getX() < RENDER_DISTANCE * enemy->getWidth() &&
        enemy->getPosition().getX() > -enemy->getWidth()) {
        _visibleEnemies.push_back(enemy);
    }

    if (enemy->getPosition().getX() < -enemy->getWidth()) {
        MapProtocol::sendEntityDeleted(enemy->getId());
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

/**
 * @brief Remove an enemy by its ID
 *
 * @param enemyId The ID of the enemy
 */
void EnemyManager::removeEnemy(int32_t enemyId) {
    auto it = std::remove_if(_enemies.begin(), _enemies.end(),
                             [enemyId](const std::shared_ptr<Enemy>& enemy) {
                                 return enemy->getId() == enemyId;
                             });

    if (it != _enemies.end()) {
        _enemies.erase(it, _enemies.end());
    }
}

/**
 * @brief Mark enemies for deletion
 *
 * @param ids The IDs of the enemies to delete
 */
void EnemyManager::markEnemiesForDeletion(const std::vector<int32_t>& ids) {
    _enemiesToDelete.insert(_enemiesToDelete.end(), ids.begin(), ids.end());
}
