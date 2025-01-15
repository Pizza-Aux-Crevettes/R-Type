/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** BulletManager.cpp
*/

#include "component/bullet/BulletManager.hpp"
#include "component/enemy/EnemyManager.hpp"
#include "component/map/MapProtocol.hpp"
#include "component/obstacle/ObstacleManager.hpp"
#include "component/player/PlayerManager.hpp"
#include "util/Config.hpp"
#include "util/Logger.hpp"

/**
 * @brief Get the BulletManager instance
 *
 * @return BulletManager&
 */
BulletManager& BulletManager::get() {
    static BulletManager instance;
    return instance;
}

/**
 * @brief Add a bullet to the manager
 *
 * @param bullet The bullet to add
 */
void BulletManager::addBullet(std::shared_ptr<Bullet> bullet) {
    std::lock_guard<std::mutex> lock(_bulletsMutex);
    _bullets.push_back(bullet);
}

/**
 * @brief Update all bullets
 *
 */
void BulletManager::updateBullets() {
    std::lock_guard<std::mutex> lock(_bulletsMutex);
    int viewportEnd = RENDER_DISTANCE * BLOCK_SIZE;

    for (auto it = _bullets.begin(); it != _bullets.end();) {
        auto& bullet = *it;

        if (bullet->getPosition().getX() > viewportEnd) {
            MapProtocol::sendEntityDeleted(bullet->getId());
            it = _bullets.erase(it);
        } else {
            bullet->move();
            ++it;
        }
    }
}

/**
 * @brief Get all bullets
 *
 * @return const std::unordered_map<int, std::shared_ptr<Bullet>>&
 */
std::vector<std::shared_ptr<Bullet>>& BulletManager::getBullets() {
    std::lock_guard<std::mutex> lock(_bulletsMutex);
    return _bullets;
}

/**
 * @brief Handle the player shoot event
 *
 * @param playerId The ID of the player who shot
 */
void BulletManager::handlePlayerShoot(int playerId) {
    auto player = PlayerManager::get().findPlayerById(playerId);
    if (!player) {
        Logger::warning("[HotkeysManager] Player " + std::to_string(playerId) +
                        " not found.");
        return;
    }

    auto position = player->getPosition();
    Point direction(1, 0);
    auto speed = BULLET_SPEED;

    auto bullet = std::make_shared<Bullet>(position, direction, speed);
    addBullet(bullet);
}

/**
 * @brief Handle the enemy shoot event
 *
 * @param enemyId The ID of the enemy who shot
 */
void BulletManager::handleEnemyShoot(int enemyId) {
    auto enemy = EnemyManager::get().getEnemies();
    auto it = std::find_if(enemy.begin(), enemy.end(),
                           [enemyId](const std::shared_ptr<Enemy>& e) {
                               return e->getId() == enemyId;
                           });

    if (it == enemy.end()) {
        Logger::warning("[BulletManager] Enemy not found. Enemy ID: " +
                        std::to_string(enemyId));
        return;
    }

    auto& enemyInstance = *it;
    Point enemyPosition = enemyInstance->getPosition();
    Point direction(-1, 0);
    double speed = BULLET_SPEED;

    auto bullet = std::make_shared<Bullet>(enemyPosition, direction, speed);
    addBullet(bullet);
}
