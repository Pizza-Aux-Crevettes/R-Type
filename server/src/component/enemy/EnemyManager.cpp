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
    // EnemyType, speed, width, height, bulletSpeed, bulletDamage,
    // shootCooldown, shootRange, health
    _enemyMapping = {
        {"E001", {EnemyType::GRUNT, 3, 50, 50, 10, 5, 800, 500, 100}},
        {"E002", {EnemyType::SNIPER, 2, 40, 40, 2, 20, 1500, 800, 1000}},
        {"E003", {EnemyType::TANK, 1, 100, 100, 2, 15, 2000, 300, 1000}},
        {"E004", {EnemyType::SWARMER, 5, 30, 30, 4, 3, 400, 200, 2000}},
        {"E005", {EnemyType::BOSS, 1, 200, 200, 7, 50, 3000, 1000, 1000}},
        {"E006", {EnemyType::DRONE, 4, 40, 40, 24, 8, 1000, 600, 1000}},
        {"E007", {EnemyType::MINION, 6, 20, 20, 4, 2, 300, 150, 1000}},
        {"E008", {EnemyType::CANNON, 0, 80, 80, 1, 25, 2000, 1000, 1000}}};

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
        enemy->move();
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
            player->takeDamage(enemy->getBulletDamage());
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
