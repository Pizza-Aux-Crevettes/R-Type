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
#include "util/Point.hpp"

class BulletManager {
  public:
    static BulletManager& get();

    void addBullet(std::shared_ptr<Bullet> bullet);
    void updateBullets();
    void forObstacles(std::vector<std::shared_ptr<Bullet>>::iterator& it,
                      std::shared_ptr<Bullet>& bullet, bool& isDeleted);
    void forPlayers(std::vector<std::shared_ptr<Bullet>>::iterator& it,
                    std::shared_ptr<Bullet>& bullet, bool& isDeleted);
    void forEnemies(std::vector<std::shared_ptr<Bullet>>::iterator& it,
                    std::shared_ptr<Bullet>& bullet, bool& isDeleted,
                    std::vector<int32_t>& enemiesToDelete);
    void invalidate(std::vector<std::shared_ptr<Bullet>>::iterator& it,
                    std::shared_ptr<Bullet>& bullet, bool& isDeleted);
    void deleteBullet(std::vector<std::shared_ptr<Bullet>>::iterator& it,
                      bool& isDeleted);
    std::vector<std::shared_ptr<Bullet>>& getBullets();
    void handlePlayerShoot(int playerId);
    void handleEnemyShoot(int enemyId, Point vector);

  private:
    BulletManager() = default;
    ~BulletManager() = default;

    std::vector<std::shared_ptr<Bullet>> _bullets;
};
