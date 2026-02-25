#include "ExplorationState.h"
#include "CombatState.h"
#include "../Game.h"
#include "../common/Utils.h"
#include <string>

void ExplorationState::onEnter(Game& game) {
    (void)game;
    // Initialization when entering exploration state can go here
}

void ExplorationState::update(Game& game) {
    auto location = game.getWorld()->getCurrentLocation();
    game.getUI()->showMessage("\033[35m[ГРА] Перед вами " + location->getName() + ". " + location->getDescription() + "\033[0m");
    if (location->hasEnemies()) {
        game.getUI()->showMessage("\033[31m[БІЙ] Раптом ви почули шелест. Тут є вороги! (Натисніть «F», щоб розпочати бій)\033[0m");
    }
}

void ExplorationState::handleInput(Game& game, char input) {
    auto& player = game.getPlayer();
    auto ui = game.getUI();
    auto& world = game.getWorld();

    // Check item usage first
    try {
        std::string inputString = std::string(1, input);
        int index = std::atoi(inputString.c_str());
        if (index >= 1 && index <= 9) {
            size_t idx = static_cast<size_t>(index - 1);
            if (idx < player->getInventory().size()) {
                player->getInventory()[idx]->use(*player);
                ui->showMessage("\033[35m[ГРА] " + player->getInventory()[idx]->getUsageMessage() + "\033[0m");
                player->getInventory().erase(player->getInventory().begin() + idx);
                return;
            }
        }
    } catch (const std::invalid_argument& e) { }

    switch (input) {
        case 'e':
            world->getCurrentLocation()->explore(*player);
            break;
        case 'f':
            game.changeState(std::make_shared<CombatState>());
            break;
        case 's':
            ui->showCharacterStatus(*player);
            break;
        case 'l':
            world->moveLeft();
            break;
        case 'r':
            world->moveRight();
            break;
        case 'z':
            if (world->getCurrentLocation()->getName() == "Село") {
                if (game.getHasSlept()) {
                    ui->showMessage("\033[35m[ГРА] Ви вже відпочали не так давно! Час рухатись далі...\033[0m");
                    break;
                }
                game.setHasSlept(true);
                int oldHealth = player->getHealth();
                player->heal(player->getMaxHealth() - player->getHealth());
                int healed = player->getHealth() - oldHealth;
                ui->showMessage("\033[35m[ГРА] Ви повернулися до будинку та добре виспались. Відновлено " + std::to_string(healed) + " очок здоров'я.\033[0m");
                Utils::sleep(1500);
            } else {
                ui->showMessage("\033[35m[ГРА] Ви можете відпочити тільки в селі! Час рухатись далі...\033[0m");
            }
            break;
        case 'h':
            ui->showHelp();
            break;
        case 'q':
            game.setIsRunning(false);
            ui->showMessage("\033[35m[ГРА] Дякуємо за гру!\033[0m");
            break;
        default:
            ui->showMessage("\033[33m[WARNING] Невідома команда. Натисніть 'H' для допомоги.\033[0m");
    }
}
