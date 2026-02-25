#include "WorldMap.h"
#include "../entities/Enemy.h"
#include "../entities/EnemyFactory.h"
#include "../items/HealthPotion.h"
#include "../items/Sword.h"
#include "../items/Axe.h"
#include "../items/Stick.h"
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <memory>

WorldMap::WorldMap() : root(nullptr), currentLocation(nullptr) {
    createWorld();
}

WorldMap::~WorldMap() {
    destructWorld();
}

// Properly traverse and clean up all nodes to avoid memory leaks
void WorldMap::destructWorld() {
    if (!root) return; 
    std::vector<LocationNode*> nodesToClean;
    std::vector<LocationNode*> toProcess;
    toProcess.push_back(root);
    while (!toProcess.empty()) {
        LocationNode* current = toProcess.back();
        toProcess.pop_back();
        bool alreadyProcessed = false;
        for (auto* processedNode : nodesToClean) {
            if (processedNode == current) {
                alreadyProcessed = true;
                break;
            }
        }
        if (!alreadyProcessed) {
            nodesToClean.push_back(current);
            LocationNode* left = current->getLeft();
            LocationNode* right = current->getRight();
            
            if (left) {
                toProcess.push_back(left);
            }
            if (right) {
                toProcess.push_back(right);
            }
        }
    }
    for (auto* node : nodesToClean) {
        if (node) {
            node->setLeft(nullptr);
            node->setRight(nullptr);
            delete node;
        }
    }
    root = nullptr;
    currentLocation = nullptr;
}

LocationNode* WorldMap::getCurrentLocation() const {
    return currentLocation;
}

void WorldMap::moveLeft() {
    if (currentLocation && currentLocation->getLeft()) {
        currentLocation = currentLocation->getLeft();
        notifyObservers(EventType::GameLog, "Ви повернули ліворуч, шукаючи щось. Як думаєте, це була гарна ідея?");
    } else {
        notifyObservers(EventType::GameLog, "Ви спробували піти ліворуч, але натрапили на бездонну прірву. Недовго думаючи, ви вирішили розвернутися.");
    }
}

void WorldMap::moveRight() {
    if (currentLocation && currentLocation->getRight()) {
        currentLocation = currentLocation->getRight();
        notifyObservers(EventType::GameLog, "Ви повернули праворуч, шукаючи щось. Як думаєте, це була гарна ідея?");
    } else {
        notifyObservers(EventType::GameLog, "Ви спробували піти праворуч, але натрапили на бездонну прірву. Недовго думаючи, ви вирішили розвернутися.");
    }
}

void WorldMap::createWorld() {
    auto* forest = new LocationNode("Темний ліс", "Густий ліс з високими, стародавніми деревами, що блокують більшу частину сонячного світла.");
    auto* cave = new LocationNode("Печера з павуками", "Темна та волога печера, заповнена павутинням.");
    auto* village = new LocationNode("Село", "Невелике, тихе село з кількома будинками та ринком.");
    auto* mountains = new LocationNode("Морозні гори", "Засніжені вершини з крижаними вітрами.");
    auto* dungeon = new LocationNode("Стародавнє підземелля", "Старе, покинуте підземелля, сповнене скарбів та небезпек.");
    
    // Create connections (binary tree structure)
    village->setLeft(forest);
    village->setRight(mountains);
    forest->setLeft(cave);
    forest->setRight(village);
    mountains->setLeft(village);
    mountains->setRight(dungeon);
    dungeon->setLeft(mountains);
    cave->setRight(forest);
    
    // Create a vector of all locations
    std::vector<LocationNode*> locations = {forest, cave, mountains, dungeon, village};
    
    // Shuffle the locations to randomize potion distribution
    std::mt19937 rng(std::time(0));
    std::shuffle(locations.begin(), locations.end(), rng);
    
    // Add health potions to random locations
    for (size_t i = 0; i < 4 && i < locations.size(); ++i) {
        locations[i]->addItem(std::make_shared<HealthPotion>());
    }
    
    // Create weapon types
    std::vector<std::function<std::shared_ptr<Item>()>> weaponGenerators = {
        []() { return std::make_shared<Sword>(); },
        []() { return std::make_shared<Axe>(); },
        []() { return std::make_shared<Stick>(); }
    };
    
    // Shuffle locations again for weapon distribution
    std::shuffle(locations.begin(), locations.end(), rng);
    
    // Add one of each weapon type to random locations
    for (size_t i = 0; i < weaponGenerators.size() && i < locations.size(); ++i) {
        locations[i]->addItem(weaponGenerators[i]());
    }
    
    forest->addEnemy(EnemyFactory::createEnemy(EnemyFactory::EnemyType::Goblin));
    forest->addEnemy(EnemyFactory::createEnemy(EnemyFactory::EnemyType::Wolf));
    
    cave->addEnemy(EnemyFactory::createEnemy(EnemyFactory::EnemyType::GiantSpider));
    cave->addEnemy(EnemyFactory::createEnemy(EnemyFactory::EnemyType::BatSwarm));
    
    dungeon->addEnemy(EnemyFactory::createEnemy(EnemyFactory::EnemyType::SkeletonWarrior));
    dungeon->addEnemy(EnemyFactory::createEnemy(EnemyFactory::EnemyType::Zombie));
    
    mountains->addEnemy(EnemyFactory::createEnemy(EnemyFactory::EnemyType::Yeti));

    // Register observers for all locations
    for (auto* loc : locations) {
        loc->addObserver(observers.empty() ? nullptr : observers.front());
    }
    
    root = village;
    currentLocation = village;
}
