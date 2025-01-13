/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** BulletManager.hpp
*/

#pragma once

#include <memory>
#include <unordered_map>
#include "component/bullet/Bullet.hpp"

class BulletManager {
  public:
    static BulletManager& get();

    void addBullet(std::shared_ptr<Bullet> bullet);
    void updateBullets();
    const std::unordered_map<int, std::shared_ptr<Bullet>>& getBullets() const;
    static void handlePlayerShoot(int playerId);

  private:
    BulletManager() = default;
    ~BulletManager() = default;

    std::unordered_map<int, std::shared_ptr<Bullet>> _bullets;
};
