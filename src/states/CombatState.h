#pragma once

#include "IGameState.h"
#include <vector>
#include <memory>
#include "../entities/Enemy.h"

/**
 * @brief Combat state managing turn-based combat.
 */
class CombatState : public IGameState {
private:
    std::vector<std::shared_ptr<Enemy>> currentEnemies;
    bool isPlayerTurn;
public:
    void onEnter(Game& game) override;
    void update(Game& game) override;
    void handleInput(Game& game, char input) override;
};
