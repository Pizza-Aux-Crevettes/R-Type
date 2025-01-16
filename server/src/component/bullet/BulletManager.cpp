/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** BulletManager.cpp
*/

#include "component/bullet/BulletManager.hpp"
#include "component/enemy/EnemyManager.hpp"
#include "component/enemy/EnemyProtocol.hpp"
#include "component/map/MapProtocol.hpp"
#include "component/obstacle/ObstacleManager.hpp"
#include "component/player/PlayerManager.hpp"
#include "component/player/PlayerProtocol.hpp"
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
    std::vector<int32_t> enemiesToDelete;

    for (auto it = _bullets.begin(); it != _bullets.end();) {
        auto& bullet = *it;
        bool isDeleted = false;

        forObstacles(it, bullet, isDeleted);
        if (isDeleted)
            continue;

        forPlayers(it, bullet, isDeleted);
        if (isDeleted)
            continue;

        forEnemies(it, bullet, isDeleted, enemiesToDelete);
        if (isDeleted)
            continue;

        invalidate(it, bullet, isDeleted);
        if (isDeleted)
            continue;

        bullet->move();
        ++it;
    }

    EnemyManager::get().markEnemiesForDeletion(enemiesToDelete);
}

/**
 * @brief Check if the bullet collides with an obstacle
 *
 * @param it The iterator of the bullet
 * @param bullet The bullet to check
 * @param isDeleted A boolean to check if the bullet is deleted
 */
void BulletManager::forObstacles(
    std::vector<std::shared_ptr<Bullet>>::iterator& it,
    std::shared_ptr<Bullet>& bullet, bool& isDeleted) {
    for (const auto& obstacle : ObstacleManager::get().getAllObstacles()) {
        if (bullet->collidesWith(obstacle->getPosition().getX(),
                                 obstacle->getPosition().getY(), OBSTACLE_SIZE,
                                 OBSTACLE_SIZE)) {
            MapProtocol::sendEntityDeleted(bullet->getId());
            it = _bullets.erase(it);
            isDeleted = true;
            break;
        }
    }
}

/**
 * @brief Check if the bullet collides with a player
 *
 * @param it The iterator of the bullet
 * @param bullet The bullet to check
 * @param isDeleted A boolean to check if the bullet is deleted
 */
void BulletManager::forPlayers(
    std::vector<std::shared_ptr<Bullet>>::iterator& it,
    std::shared_ptr<Bullet>& bullet, bool& isDeleted) {
    for (const auto& player : PlayerManager::get().getPlayers()) {
        if (bullet->getType() == BulletType::ENEMY &&
            bullet->collidesWith(player->getPosition().getX(),
                                 player->getPosition().getY(), PLAYER_WIDTH,
                                 PLAYER_HEIGHT)) {
            player->takeDamage(bullet->getDamage());
            PlayerProtocol::sendPlayerTakeDamage(player->getId(),
                                                 bullet->getDamage());

            MapProtocol::sendEntityDeleted(bullet->getId());
            it = _bullets.erase(it);
            isDeleted = true;
            break;
        }
    }
}

/**
 * @brief Check if the bullet collides with an enemy
 *
 * @param it The iterator of the bullet
 * @param bullet The bullet to check
 * @param isDeleted A boolean to check if the bullet is deleted
 * @param enemiesToDelete The list of enemies to delete
 */
void BulletManager::forEnemies(
    std::vector<std::shared_ptr<Bullet>>::iterator& it,
    std::shared_ptr<Bullet>& bullet, bool& isDeleted,
    std::vector<int32_t>& enemiesToDelete) {
    for (const auto& enemy : EnemyManager::get().getEnemies()) {
        if (bullet->getType() == BulletType::PLAYER &&
            bullet->collidesWith(enemy->getPosition().getX(),
                                 enemy->getPosition().getY(), enemy->getWidth(),
                                 enemy->getHeight())) {
            enemy->takeDamage(bullet->getDamage());
            EnemyProtocol::sendEnemyTakeDamage(enemy->getId(),
                                               bullet->getDamage());

            if (enemy->getHealth() <= 0 &&
                enemy->getHealth() != ENEMY_FALLBACK_VALUE) {
                enemy->setHealth(ENEMY_FALLBACK_VALUE);
                MapProtocol::sendEntityDeleted(enemy->getId());
                enemiesToDelete.push_back(enemy->getId());
            }

            MapProtocol::sendEntityDeleted(bullet->getId());
            it = _bullets.erase(it);
            isDeleted = true;
            break;
        }
    }
}

/**
 * @brief Invalidate a bullet
 *
 * @param it The iterator of the bullet
 * @param bullet The bullet to invalidate
 * @param isDeleted A boolean to check if the bullet is deleted
 */
void BulletManager::invalidate(
    std::vector<std::shared_ptr<Bullet>>::iterator& it,
    std::shared_ptr<Bullet>& bullet, bool& isDeleted) {
    if (bullet->getPosition().getX() > RENDER_DISTANCE * OBSTACLE_SIZE ||
        bullet->getPosition().getX() < -OBSTACLE_SIZE) {
        MapProtocol::sendEntityDeleted(bullet->getId());
        it = _bullets.erase(it);
        isDeleted = true;
    }
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
    auto bullet = std::make_shared<Bullet>(
        player->getPosition(), direction, PLAYER_BULLET_SPEED,
        BulletType::PLAYER, PLAYER_BULLET_DAMAGE);
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

    auto bullet = std::make_shared<Bullet>(
        enemy->getPosition(), direction, enemy->getBulletSpeed(),
        BulletType::ENEMY, enemy->getBulletDamage());
    addBullet(bullet);
}
