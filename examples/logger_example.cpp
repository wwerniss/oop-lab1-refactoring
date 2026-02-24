/// Example demonstrating how to use Logger.

#include "Logger.h"

int main() {
    Logger& logger = Logger::getInstance();
    logger.gameLog("Player started the game");
    logger.combatLog("Player attacked enemy for 10 damage");
    logger.info("Some info message");
    logger.error("Oops, an error!");
    return 0;
}