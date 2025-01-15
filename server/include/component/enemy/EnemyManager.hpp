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
    int16_t speed;
    int16_t width;
    int16_t height;
    int16_t bulletSpeed;
    int16_t bulletDamage;
    int16_t shootCooldown;
    int16_t shootRange;
};

class EnemyManager {
  public:
    static EnemyManager& get();

    std::string EnemyTypeToString(EnemyType type) const;
    void addEnemy(const std::shared_ptr<Enemy>& enemy);
    std::shared_ptr<Enemy> findById(int32_t enemyId) const;
    void updateEnemies();
    const std::vector<std::shared_ptr<Enemy>>& getEnemies() const;
    const std::vector<std::shared_ptr<Enemy>>& getVisibleEnemies() const;
    bool isEnemyCodeValid(const std::string& code) const;
    EnemyProperties getEnemyProperties(const std::string& code) const;
    void removeEnemy(int32_t enemyId);
    void markEnemiesForDeletion(const std::vector<int32_t>& ids);

  private:
    EnemyManager();
    ~EnemyManager();

    std::unordered_map<std::string, EnemyProperties> _enemyMapping;
    std::vector<std::shared_ptr<Enemy>> _enemies;
    std::vector<std::shared_ptr<Enemy>> _visibleEnemies;
    std::vector<int32_t> _enemiesToDelete;
};
