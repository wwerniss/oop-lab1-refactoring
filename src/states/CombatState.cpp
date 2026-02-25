#include "CombatState.h"
#include "ExplorationState.h"
#include "../Game.h"
#include "../common/Utils.h"
#include <unistd.h>

void CombatState::onEnter(Game& game) {
    auto location = game.getWorld()->getCurrentLocation();
    if (!location->hasEnemies()) {
        game.getUI()->showMessage("\033[35m[ГРА] Тут немає ворогів, з якими можна було б битися!\033[0m");
        game.changeState(std::make_shared<ExplorationState>());
        return;
    }
    
    // Copy the references to enemies
    currentEnemies = location->getEnemies();
    isPlayerTurn = true;
    game.getUI()->showMessage("\033[35m[ГРА] Ви розпочали бій!\033[0m");
}

void CombatState::update(Game& game) {
    auto& player = game.getPlayer();
    auto ui = game.getUI();

    if (currentEnemies.empty()) {
        ui->showMessage("\033[31m[БІЙ] Всі вороги переможені!\033[0m");
        game.changeState(std::make_shared<ExplorationState>());
        return;
    }

    if (!player->isAlive()) {
        ui->showGameOver();
        game.setIsRunning(false);
        return;
    }

    ui->showMessage("\033[35m[ГРА] Твоє шосте чуття підказує тобі, що ти маєш " + std::to_string(player->getHealth()) + " HP.\033[0m");
    ui->showCombatStatus(*player, currentEnemies);
}

void CombatState::handleInput(Game& game, char input) {
    auto& player = game.getPlayer();
    auto ui = game.getUI();
    auto location = game.getWorld()->getCurrentLocation();

    if (input == 'a') {
        ui->showMessage("Якого ворога ви хочете атакувати? (1-" + std::to_string(currentEnemies.size()) + ")");
        int target = 0;
        char targetInput;
        
        do {
            targetInput = ui->getCharInputNonBlocking();
            if (targetInput >= '1' && targetInput <= '9') {
                target = targetInput - '0';
                break;
            }
            usleep(100000);
        } while (targetInput == -1);
        
        if (target > 0 && target <= static_cast<int>(currentEnemies.size())) {
            player->attackTarget(*currentEnemies[target-1]);
            
            // Check if enemy is defeated
            if (!currentEnemies[target-1]->isAlive()) {
                int exp = std::static_pointer_cast<Enemy>(currentEnemies[target-1])->getExperienceReward();
                player->gainExperience(exp);
                ui->showMessage("\033[31m[БІЙ] " + currentEnemies[target-1]->getName() + " зазнав поразки!\033[0m");
                location->removeEnemy(target-1);
                
                // Refresh local enemies list from location
                currentEnemies = location->getEnemies();
            }
        } else {
            ui->showMessage("\033[33m[WARNING] Недійсна ціль!\033[0m");
            return; // Don't process enemy turn if invalid action
        }
    } else if (input == 'u') {
        ui->showMessage("\033[35m[ГРА] Використання предметів під час бою ще не реалізовано!\033[0m");
        return;
    } else if (input == 'r') {
        if (Utils::chance(70)) {
            ui->showMessage("\033[35m[ГРА] Ви успішно втекли!\033[0m");
            game.changeState(std::make_shared<ExplorationState>());
            return;
        } else {
            ui->showMessage("\033[35m[ГРА] Вам не вдалося втекти!\033[0m");
        }
    } else {
        ui->showMessage("\033[33m[WARNING] Невідома команда!\033[0m");
        return;
    }

    // Enemy Turn Context (only reaches here if player action was valid)
    if (!currentEnemies.empty()) {
        for (auto& enemy : currentEnemies) {
            if (enemy->isAlive()) {
                enemy->attackTarget(*player);
                
                if (!player->isAlive()) {
                    ui->showGameOver();
                    game.setIsRunning(false);
                    return;
                }
            }
        }
        Utils::sleep(1000);
    }
}
