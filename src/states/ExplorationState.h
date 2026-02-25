#pragma once

#include "IGameState.h"

/**
 * @brief Exploration state where the player moves around the map and manages inventory.
 */
class ExplorationState : public IGameState {
public:
    void onEnter(Game& game) override;
    void update(Game& game) override;
    void handleInput(Game& game, char input) override;
};
