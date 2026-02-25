#pragma once

#include "IUserInterface.h"
#include <iostream>

/**
 * @brief Console implementation of the IUserInterface.
 * 
 * Implements the input/output operations targeting standard terminal console.
 */
class ConsoleUI : public IUserInterface {
public:
    void clearScreen() override;
    void showTitle() override;
    void showHelp() override;
    void showGameOver() override;
    
    void showMessage(const std::string& message) override;
    void showCharacterStatus(const Character& character) override;
    void showCombatStatus(const Character& player, const std::vector<std::shared_ptr<Enemy>>& enemies) override;
    
    char getCharInput() override;
    char getCharInputNonBlocking() override;
    std::string getStringInput(const std::string& prompt) override;
};
