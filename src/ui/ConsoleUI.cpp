#include "ConsoleUI.h"
#include "../common/Utils.h"
#include "../entities/Character.h"
#include "../entities/Enemy.h"
#include "../items/Weapon.h"
#include "../items/Item.h"

void ConsoleUI::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void ConsoleUI::showTitle() {
    std::cout << "__________.__                .__                 ________                __                                              \n";
    std::cout << "\\______   \\  | _____  _______|__| ____    ____   \\______ \\ _____ _______|  | __ ____   ____   ______ ______          \n";
    std::cout << " |    |  _/  | \\__  \\ \\___   /  |/    \\  / ___\\   |    |  \\\\__  \\\\_  __ \\  |/ //    \\_/ __ \\ /  ___//  ___/  \n";
    std::cout << " |    |   \\  |__/ __ \\_/    /|  |   |  \\/ /_/  >  |    `   \\/ __ \\|  | \\/    <|   |  \\  ___/ \\___ \\ \\___ \\    \n";
    std::cout << " |______  /____(____  /_____ \\__|___|  /\\___  /  /_______  (____  /__|  |__|_ \\___|  /\\___  >____  >____  >          \n";
    std::cout << "        \\/          \\/      \\/       \\//_____/           \\/     \\/           \\/    \\/     \\/     \\/     \\/    \n";
}

void ConsoleUI::showHelp() {
    std::cout << "\n=== Команди ===\n"
              << "[S]тaтус - Показати стан персонажа\n"
              << "[E]ксплоруй - Дослідити локацію\n"
              << "[F]айт - Битися з ворогами\n"
              << "[I]нвентар - Відкрити інвентар\n"
              << "[L]іворуч - Перейти в локацію ліворуч\n"
              << "[R]праворуч - Перейти в локацію праворуч\n"
              << "[V]село - Повернутися до села\n"
              << "[Z]сон - Відпочити у селі (тільки у селі)\n"
              << "[Q]вихід - Вийти з гри\n"
              << "[H]елп - Показати довідку\n"
              << std::endl;
}

void ConsoleUI::showGameOver() {
    // This will now just print via UI instead of Logger maybe, 
    // or Game can just output generic game over
    std::cout << "\033[31m[БІЙ] Стікаючи кров’ю, ви намагалися втекти, але зрозуміли, що більше не зможете цього зробити. Ваші пригоди добігли кінця...\033[0m\n";
}

void ConsoleUI::showMessage(const std::string& message) {
    std::cout << message << std::endl;
}

void ConsoleUI::showCharacterStatus(const Character& character) {
    std::cout << "\n=== " << character.getName() << " === ";
    std::cout << "Рівень: " << character.getLevel() << " | ";
    std::cout << "Здоров'я: " << character.getHealth() << "/" << character.getMaxHealth() << " | ";
    std::cout << "Атака: " << character.getAttack() << " | ";
    std::cout << "Захист: " << character.getDefense() << std::endl;

    if (character.hasWeaponEquipped()) {
        std::cout << "\nУ ваших руках " << character.getEquippedWeaponName() << std::endl;
    } else {
        std::cout << "\nУ ваших руках немає жодної зброї!" << std::endl;
    }
    
    auto inventory = character.getInventory();
    int counter = 0;
    if (!inventory.empty()) {
        std::cout << "\nІнвентар:";
        for (const auto& item : inventory) {
            std::cout << "\n" << ++counter << ". " << item->getName() << " (" << item->getDescription() << ")";
        }
        std::cout << "\nНатисніть номер предмету на клавіатурі, щоб використати його.";
    } else {
        std::cout << "\nВаш інвентар порожній.";
    }
    std::cout << std::endl << std::endl;
}

void ConsoleUI::showCombatStatus(const Character& player, const std::vector<std::shared_ptr<Enemy>>& enemies) {
    (void)player;
    std::cout << "Вороги: ";
    for (size_t i = 0; i < enemies.size(); ++i) {
        std::cout << "[" << (i+1) << "] " << enemies[i]->getName() 
                  << " (HP: " << enemies[i]->getHealth() 
                  << "/" << enemies[i]->getMaxHealth() << ") ";
    }
    std::cout << std::endl;
}

char ConsoleUI::getCharInput() {
    char input;
    std::cin >> input;
    return input;
}

char ConsoleUI::getCharInputNonBlocking() {
    return Utils::getCharNonBlock();
}

std::string ConsoleUI::getStringInput(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}
