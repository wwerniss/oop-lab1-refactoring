/// Example demonstrating how to create new characters based on Character class.

#include "Player.h"
#include "Character.h"

// Adding some peaceful character
class PeacefulCharacter : public Character {
    public: 
        void attackTarget(Character& target) {
            return; // Not attacs anyone
        }
};