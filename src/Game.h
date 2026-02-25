#pragma once

/**
 * @brief The main game class that controls the overall game flow.
 * 
 * This class manages the game loop, player interaction, world navigation,
 * and combat system. It serves as the central hub for all game operations.
 * 
 * @example examples/game_example.cpp
 */
#include <memory>
#include <iostream>
#include "entities/Player.h"
#include "world/WorldMap.h"
#include "common/Logger.h"
#include "common/Utils.h"
#include "ui/IUserInterface.h"
#include "states/IGameState.h"

/**
 * @brief The main game class that controls the overall game flow.
 * 
 * This class manages the game loop, player interaction, world navigation,
 * and combat system. It serves as the central hub for all game operations.
 */
class Game {
private:
    std::shared_ptr<IUserInterface> ui;
    bool isRunning;
    std::unique_ptr<Player> player;
    std::unique_ptr<WorldMap> world;
    bool hasSlept; // Track if player has already slept
    std::shared_ptr<IGameState> currentState;
    
    /**
     * @brief Displays game over message.
     * 
     * Shows a descriptive message when the player's character dies.
     */
    void showGameOver();
    
    // Removed: void handleCombat();
    
public:
    /**
     * @brief Constructs a new Game instance.
     * 
     * Initializes the game with default values and prepares the game state.
     */
    Game();
    
    /**
     * @brief Gets the singleton instance of the Game class.
     * 
     * This method provides access to the single instance of the Game class
     * using the singleton pattern.
     * 
     * @return Reference to the singleton Game instance
     * @example
     * Game& game = Game::getInstance();
     */
    static Game& getInstance() {
        static Game instance;
        return instance;
    }
    
    /**
     * @brief Runs the main game loop.
     * 
     * This method starts the game and controls the main execution flow,
     * handling user input, world navigation, and combat.
     * 
     * @throws std::runtime_error If there are issues with game initialization or execution
     */
    void run();

    // -- State Pattern methods --
    void changeState(std::shared_ptr<IGameState> newState);

    // -- Getters & Setters for States --
    std::unique_ptr<Player>& getPlayer() { return player; }
    std::unique_ptr<WorldMap>& getWorld() { return world; }
    std::shared_ptr<IUserInterface> getUI() { return ui; }
    
    bool getIsRunning() const { return isRunning; }
    void setIsRunning(bool running) { isRunning = running; }
    
    bool getHasSlept() const { return hasSlept; }
    void setHasSlept(bool slept) { hasSlept = slept; }
};
