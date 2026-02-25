#pragma once

// Forward declaration
class Game;

/**
 * @brief Interface for Game States.
 * 
 * Part of the State pattern to decouple monolithic Game loops into 
 * distinct manageable behaviors (e.g. Exploration, Combat).
 */
class IGameState {
public:
    virtual ~IGameState() = default;

    /**
     * @brief Called when the state is first entered.
     */
    virtual void onEnter(Game& game) = 0;

    /**
     * @brief Called every frame/tick to update the state logic.
     */
    virtual void update(Game& game) = 0;

    /**
     * @brief Handles user input specific to this state.
     * 
     * @param game The main Game context
     * @param input The character input from the user
     */
    virtual void handleInput(Game& game, char input) = 0;
};
