/// Example demonstrating how to use Item.

#include "HealthPotion.h"
#include "Player.h"

int main() {
    Player player("Hero");
    Item* item = new HealthPotion();
    item->use(player);
}
