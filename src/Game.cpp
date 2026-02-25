#include "Game.h"
#include <unistd.h> // for usleep
#include "ui/ConsoleUI.h"
#include "states/ExplorationState.h"

Game::Game() : isRunning(false), hasSlept(false) {
    ui = std::make_shared<ConsoleUI>();
    Logger::getInstance().setUI(ui);
}
void Game::changeState(std::shared_ptr<IGameState> newState) {
    currentState = newState;
    if (currentState) {
        currentState->onEnter(*this);
    }
}

void Game::run() {
    ui->clearScreen();
    ui->showTitle();
    ui->showMessage("\nBlazing Darkness | Version 0.1 | Made by wwerniss\n");
    std::string playerName = ui->getStringInput("Введіть ім'я персонажа: ");
    
    if (playerName.empty()) {
        playerName = "Герой";
    }
    
    player = std::make_unique<Player>(playerName);
    player->addObserver(&Logger::getInstance());
    world = std::make_unique<WorldMap>();
    world->addObserver(&Logger::getInstance());
    isRunning = true;

    ui->showMessage("Гра: [E] - Досліджувати [F] - Розпочати бій [S] - Статус та інвентар [L] - Ліворуч [R] - Праворуч [Z] - Спати [H] - Допомога [Q] - Вийти \nБій: [A] - Атакувати [U] - Використати предмет [R] - Втекти\n");

    ui->showMessage("\033[35m[ГРА] " + playerName + " прокину(вся/лась) в маленькому будинку...\033[0m");
    Utils::sleep(2000);
    ui->showMessage("\033[35m[ГРА] Двері зі скрипом відчиняються, ви виходите і бачите село з кількома будинками та крамницями.\033[0m");
    Utils::sleep(2000);
    ui->showMessage("\033[35m[ГРА] Останнє, що ви пам'ятаєте, це ім'я Ейрін та вашу вдалу втечу від монстрів.\033[0m");
    Utils::sleep(2000);
    ui->showMessage("\033[35m[ГРА] Ви готові розпочати свою пригоду! Чекаємо на ваші дії...\033[0m");
    
    Utils::setRawMode(true);
    changeState(std::make_shared<ExplorationState>());

    while (isRunning) {
        if (currentState) {
            currentState->update(*this);
            
            // Wait for input
            char input;
            do {
                input = std::tolower(ui->getCharInputNonBlocking());
            } while (input == -1 && isRunning); // only wait while running (avoids infinite loop on exit)
            
            if (isRunning && currentState && input != -1) {
                currentState->handleInput(*this, input);
            }
        }
        
        usleep(50000); // 50ms loop buffer
    }
    
    Utils::setRawMode(false);
}
