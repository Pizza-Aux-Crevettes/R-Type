/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** BulletManager.cpp
*/

#include "component/bullet/BulletManager.hpp"
#include "component/map/MapManager.hpp"
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
    _bullets[bullet->getId()] = bullet;

    Logger::info("[BulletManager] Added bullet with ID: " +
                 std::to_string(bullet->getId()));
}

/**
 * @brief Update all bullets
 *
 */
void BulletManager::updateBullets() {
    auto viewport = MapManager::get().getCurrentMap()->getViewport();
    int viewportWidth = RENDER_DISTANCE * BLOCK_SIZE;
    int viewportHeight = RENDER_DISTANCE * BLOCK_SIZE;

    for (auto it = _bullets.begin(); it != _bullets.end();) {
        auto& bullet = it->second;
        bullet->move();

        if (bullet->isOutsideViewport(viewportWidth, viewportHeight)) {
            Logger::info("[BulletManager] Bullet " +
                         std::to_string(bullet->getId()) +
                         " removed (out of viewport).");
            it = _bullets.erase(it);
        } else {
            ++it;
        }
    }
}

/**
 * @brief Get all bullets
 *
 * @return const std::unordered_map<int, std::shared_ptr<Bullet>>&
 */
const std::unordered_map<int, std::shared_ptr<Bullet>>&
BulletManager::getBullets() const {
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
    auto direction = Point(1, 0);
    auto speed = BULLET_SPEED;

    auto bullet = std::make_shared<Bullet>(position, direction, speed);
    BulletManager::get().addBullet(bullet);

    Logger::info("[HotkeysManager] Player " + std::to_string(playerId) +
                 " fired a bullet.");
}
