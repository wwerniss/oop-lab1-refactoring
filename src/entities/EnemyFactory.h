#pragma once

#include "Enemy.h"
#include <memory>
#include <string>

/**
 * @brief Factory class for creating enemies.
 * 
 * Provides centralized methods for instantiating concrete configurations
 * of enemies, allowing easy scaling and balancing.
 */
class EnemyFactory {
public:
    enum class EnemyType {
        Goblin,
        Wolf,
        GiantSpider,
        BatSwarm,
        SkeletonWarrior,
        Zombie,
        Yeti
    };

    /**
     * @brief Creates an enemy of a specific type.
     * 
     * @param type The type of enemy to create
     * @return A shared pointer to the newly created Enemy
     */
    static std::shared_ptr<Enemy> createEnemy(EnemyType type) {
        switch (type) {
            case EnemyType::Goblin:
                return std::make_shared<Enemy>("Гоблін", 2, 15, 4, 2, 25);
            case EnemyType::Wolf:
                return std::make_shared<Enemy>("Вовк", 1, 10, 3, 1, 15);
            case EnemyType::GiantSpider:
                return std::make_shared<Enemy>("Гігантський павук", 3, 20, 5, 3, 35);
            case EnemyType::BatSwarm:
                return std::make_shared<Enemy>("Рій кажанів", 1, 5, 2, 0, 10);
            case EnemyType::SkeletonWarrior:
                return std::make_shared<Enemy>("Воїн скелет", 5, 30, 7, 5, 50);
            case EnemyType::Zombie:
                return std::make_shared<Enemy>("Зомбі", 3, 25, 5, 2, 30);
            case EnemyType::Yeti:
                return std::make_shared<Enemy>("Єті", 7, 40, 10, 8, 75);
            default:
                return std::make_shared<Enemy>("Невідомий монстр", 1, 10, 1, 0, 10);
        }
    }
};
