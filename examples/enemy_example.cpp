/// Example demonstrating how to use Enemy.

#include "Enemy.h"
#include "Player.h"

int main() {
    Player player("Hero");
    Enemy enemy("Goblin", 1, 15, 3, 1, 25);
    enemy.attackTarget(player);
}