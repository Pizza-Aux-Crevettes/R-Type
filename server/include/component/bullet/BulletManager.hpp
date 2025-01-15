/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** BulletManager.hpp
*/

#pragma once

#include <memory>
#include <vector>
#include "component/bullet/Bullet.hpp"

class BulletManager {
  public:
    static BulletManager& get();

    void addBullet(std::shared_ptr<Bullet> bullet);
    void updateBullets();
    std::vector<std::shared_ptr<Bullet>>& getBullets();
    void handlePlayerShoot(int playerId);
    void handleEnemyShoot(int enemyId);

  private:
    BulletManager() = default;
    ~BulletManager() = default;

    std::vector<std::shared_ptr<Bullet>> _bullets;
    std::mutex _bulletsMutex;
};
