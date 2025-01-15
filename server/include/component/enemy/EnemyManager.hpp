/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** EnemyManager.hpp
*/

#include <memory>
#include <unordered_map>
#include <vector>
#include "component/enemy/Enemy.hpp"

struct EnemyProperties {
    EnemyType type;
    int width;
    int height;
    double speed;
    double bulletSpeed;
    int shootCooldown;
    int shootRange;
};

class EnemyManager {
  public:
    static EnemyManager& get();

    std::string EnemyTypeToString(EnemyType type) const;
    void addEnemy(const std::shared_ptr<Enemy>& enemy);
    std::shared_ptr<Enemy> findById(int enemyId) const;
    void updateEnemies();
    const std::vector<std::shared_ptr<Enemy>>& getEnemies() const;
    const std::vector<std::shared_ptr<Enemy>>& getVisibleEnemies() const;
    bool isEnemyCodeValid(const std::string& code) const;
    EnemyProperties getEnemyProperties(const std::string& code) const;

  private:
    EnemyManager();
    ~EnemyManager();

    std::unordered_map<std::string, EnemyProperties> _enemyMapping;
    std::vector<std::shared_ptr<Enemy>> _enemies;
    std::vector<std::shared_ptr<Enemy>> _visibleEnemies;
};
