/// Example demonstrating how to use Utils.

#include "Utils.h"

int main() {
    int randomValue = Utils::getRandomInt(1, 10);
    bool success = Utils::chance(75);
    std::cout << "Random value: " << randomValue << std::endl;
    std::cout << "Success: " << success << std::endl;
    return 0;
}