#ifndef GAME_INPUTS_H
#define GAME_INPUTS_H

#include <string>
#include <vector>

// List of valid inputs for the game
const std::vector<std::string> validInputs = {
    "look",          // Look around the room
    "move",          // Move to another room
    "take key",      // Pick up the key
    "take antidote", // Pick up the antidote
    "use antidote",  // Use the antidote to cure poison
    "interact",      // Interact with objects or scenarios
    "open chest",    // Open the chest in room 7
    "unlock exit",   // Unlock the exit with the key
    "north",         // Move north
    "south",         // Move south
    "east",          // Move east
    "west",          // Move west
    "quit",          // Quit the game
    "hurt"           // Example action to lose health
};

#endif // GAME_INPUTS_H