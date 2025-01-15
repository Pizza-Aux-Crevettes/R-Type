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
    _bullets.push_back(bullet);
}

/**
 * @brief Update all bullets
 *
 */
void BulletManager::updateBullets() {
    int viewportEnd = RENDER_DISTANCE * OBSTACLE_SIZE;
    std::vector<int32_t> enemiesToDelete;

    for (auto it = _bullets.begin(); it != _bullets.end();) {
        auto& bullet = *it;
        bool isDeleted = false;

        for (const auto& obstacle : ObstacleManager::get().getAllObstacles()) {
            if (bullet->collidesWith(obstacle->getPosition().getX(), obstacle->getPosition().getY(),
                                     OBSTACLE_SIZE, OBSTACLE_SIZE)) {
                MapProtocol::sendEntityDeleted(bullet->getId());
                it = _bullets.erase(it);
                isDeleted = true;
                break;
            }
        }
        if (isDeleted) continue;

        for (const auto& player : PlayerManager::get().getPlayers()) {
            if (bullet->collidesWith(player->getPosition().getX(), player->getPosition().getY(),
                                     PLAYER_WIDTH, PLAYER_HEIGHT)) {
                MapProtocol::sendEntityDeleted(bullet->getId());
                it = _bullets.erase(it);
                isDeleted = true;
                break;
            }
        }
        if (isDeleted) continue;

        for (const auto& enemy : EnemyManager::get().getEnemies()) {
            if (bullet->getType() == BulletType::PLAYER && bullet->collidesWith(enemy->getPosition().getX(),
                                                                              enemy->getPosition().getY(),
                                                                              enemy->getWidth(), enemy->getHeight())) {
                enemy->takeDamage(PLAYER_BULLET_DAMAGE);
                if (enemy->getHealth() <= 0) {
                    MapProtocol::sendEntityDeleted(enemy->getId());
                    enemiesToDelete.push_back(enemy->getId());
                }
                MapProtocol::sendEntityDeleted(bullet->getId());
                it = _bullets.erase(it);
                isDeleted = true;
                break;
            }
        }
        if (isDeleted) continue;

        if (bullet->getPosition().getX() > viewportEnd || bullet->getPosition().getX() < 0 || 
            bullet->getPosition().getY() > viewportEnd || bullet->getPosition().getY() < 0) {
            MapProtocol::sendEntityDeleted(bullet->getId());
            it = _bullets.erase(it);
            continue;
        } 

        bullet->move();
        ++it;
    }

    EnemyManager::get().markEnemiesForDeletion(enemiesToDelete);
}

/**
 * @brief Get all bullets
 *
 * @return const std::unordered_map<int, std::shared_ptr<Bullet>>&
 */
std::vector<std::shared_ptr<Bullet>>& BulletManager::getBullets() {
    return _bullets;
}

/**
 * @brief Handle the player shoot event
 *
 * @param playerId The ID of the player who shot
 */
void BulletManager::handlePlayerShoot(int playerId) {
    auto player = PlayerManager::get().findByID(playerId);
    if (!player)
        return;

    Point direction(1, 0);
    auto bullet = std::make_shared<Bullet>(player->getPosition(), direction, PLAYER_BULLET_SPEED, BulletType::PLAYER);
    addBullet(bullet);
}

/**
 * @brief Handle the enemy shoot event
 *
 * @param enemyId The ID of the enemy who shot
 */
void BulletManager::handleEnemyShoot(int enemyId, Point direction) {
    auto enemy = EnemyManager::get().findById(enemyId);
    if (!enemy)
        return;

    auto bullet = std::make_shared<Bullet>(enemy->getPosition(), direction, enemy->getBulletSpeed(), BulletType::ENEMY);
    addBullet(bullet);
}
