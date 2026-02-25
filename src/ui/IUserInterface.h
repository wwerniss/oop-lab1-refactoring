#pragma once

#include <string>
#include <vector>
#include <memory>

class Character;
class Enemy;

/**
 * @brief User Interface Abstraction.
 * 
 * Provides an interface for all interactions with the user, 
 * decoupling the game logic from direct console manipulation.
 */
class IUserInterface {
public:
    virtual ~IUserInterface() = default;

    // Display functions
    virtual void clearScreen() = 0;
    virtual void showTitle() = 0;
    virtual void showHelp() = 0;
    virtual void showGameOver() = 0;
    
    virtual void showMessage(const std::string& message) = 0;
    virtual void showCharacterStatus(const Character& character) = 0;
    virtual void showCombatStatus(const Character& player, const std::vector<std::shared_ptr<Enemy>>& enemies) = 0;
    
    // Input functions
    virtual char getCharInput() = 0;
    virtual char getCharInputNonBlocking() = 0;
    virtual std::string getStringInput(const std::string& prompt) = 0;
};
