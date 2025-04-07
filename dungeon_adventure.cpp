// Welcome to "Escape the Dungeon"
// You find yourself trapped in a dark dungeon.
// Your mission is to find a way out.
// You will encounter various rooms, objects, and challenges along the way.
// Good luck!



#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Struct for objects in the game
struct Object {
    std::string name;        // Name of the object
    std::string description; // Description of the object
    int location;            // Location of the object in the dungeon
};

// Struct for rooms in the game
struct Room {
    std::string description; // Description of the room
    std::map<std::string, int> directions; // Possible directions and their outcomes
    bool hasTrap = false;    // Whether the room contains a trap
};

// Global variables
int location = 0;          // Player's current location (room index)
bool gameRunning = true;   // Whether the game is running
int health = 100;          // Player's health
bool poisoned = false;     // Whether the player is poisoned
bool hasAntidote = false;  // Whether the player has picked up the antidote
bool hasKey = false;       // Track if the player has the key

// Function to move the player
void movePlayer(const std::string& direction, const std::vector<Room>& rooms) {
    if (rooms[location].directions.count(direction)) {
        int nextRoom = rooms[location].directions.at(direction);
        if (nextRoom == -1) { // -1 indicates a deadly trap
            std::cout << "You walked into a pit of spikes and died. Game over.\n";
            gameRunning = false;
        } else if (nextRoom == -2) { // -2 indicates a poison trap
            poisoned = true;
            std::cout << "You walked into a poison trap! You are now poisoned.\n";
        } else if (location == 9 && direction == "north") { // Exit condition
            if (hasKey) {
                std::cout << "You use the key to unlock the exit and escape the dungeon! Congratulations, you win!\n";
                gameRunning = false; // End the game
            } else {
                std::cout << "The exit is locked. You need a key to unlock it.\n";
            }
        } else {
            location = nextRoom;
            std::cout << "You have moved to the " << direction << ".\n";
        }
    } else {
        std::cout << "You cannot move in that direction.\n";
    }
}

// Function to apply poison effects
void applyPoison() {
    if (poisoned) {
        health -= 5; // Lose 5 health per turn if poisoned
        std::cout << "You feel weak as the poison courses through your veins. Health is now " << health << ".\n";
        if (health <= 0) {
            std::cout << "The poison has killed you. Game over.\n";
            gameRunning = false;
        }
    }
}

int main() {
    // Define rooms with possible directions
    std::vector<Room> rooms = {
        {"a small, dank cell with a rusted iron door.", {{"north", 1}, {"east", -1}, {"west", -2}, {"south", -1}}}, // Room 0
        {"a dimly lit corridor with stone walls and 4 hallways.", {{"north", 2}, {"east", -2}, {"west", -1}, {"south", 0}}},      // Room 1
        {"a large hall with a high ceiling and flickering torches.", {{"north", -1}, {"east", 3}, {"west", -2}, {"south", 1}}}, // Room 2
        {"a narrow passage filled with cobwebs.", {{"north", 4}, {"east", -2}, {"west", -1}, {"south", 2}}},       // Room 3
        {"a room with a deep pit in the center.", {{"north", 5}, {"east", -1}, {"west", -2}, {"south", 3}}},       // Room 4
        {"a library filled with dusty books and broken shelves. One book sticks out slightly.", {{"north", -1}, {"east", -2}, {"west", 6}, {"south", 4}}}, // Room 5
        {"a treasure room with glittering gold and jewels.", {{"north", 7}, {"east", -1}, {"west", -2}, {"south", 5}}}, // Room 6
        {"a kitchen with rusty utensils and a plain chest in the corner.", {{"north", -2}, {"east", 8}, {"west", -1}, {"south", 6}}}, // Room 7
        {"a prison guard's room with a broken chair and a table.", {{"north", 9}, {"east", -1}, {"west", -2}, {"south", 7}}}, // Room 8
        {"a mysterious chamber with glowing runes on the walls.", {{"north", -1}, {"east", -1}, {"west", -1}, {"south", 8}}} // Room 9 (Exit)
    };

    // Define objects
    Object key = {"key", "A small iron key.", 5}; // Key is in room 5 (library)
    Object antidote = {"antidote", "A vial of antidote to cure poison.", 7}; // Antidote is in room 7 (inside chest)

    bool chestOpened = false; // Track if the chest in room 7 has been opened
    bool keyRevealed = false; // Track if the key in the library has been revealed

    while (gameRunning) {
        std::string input;
        std::cout << "You are in " << rooms[location].description << "\n";
        std::cout << "Health: " << health << "\n"; // Display health
        if (poisoned) {
            std::cout << "You are poisoned! Find an antidote quickly.\n";
        }

        std::cout << "What would you like to do? (north/south/east/west/look/interact)\n";
        std::getline(std::cin, input);

        // Apply poison effects at the start of each turn
        applyPoison();

        if (input == "north" || input == "south" || input == "east" || input == "west") {
            movePlayer(input, rooms);
        } else if (input == "look") {
            if (location == 5 && !keyRevealed) {
                std::cout << "You notice a book sticking out slightly. Behind it, you find a small iron key!\n";
                keyRevealed = true;
            } else {
                std::cout << "You look around but find nothing of interest.\n";
            }
        } else if (input == "take key" && location == key.location && keyRevealed && !hasKey) {
            hasKey = true;
            std::cout << "You have picked up the key.\n";
        } else if (input == "interact" && location == 7 && !chestOpened) {
            std::cout << "You open the plain chest and find a vial of antidote inside.\n";
            chestOpened = true;
        } else if (input == "take antidote" && location == antidote.location && chestOpened && !hasAntidote) {
            hasAntidote = true;
            std::cout << "You have picked up the antidote.\n";
        } else if (input == "use antidote" && hasAntidote) {
            if (poisoned) {
                poisoned = false;
                std::cout << "You use the antidote and feel the poison leave your body. You are cured!\n";
            } else {
                std::cout << "You are not poisoned, so the antidote has no effect.\n";
            }
        } else if (input == "quit") {
            gameRunning = false;
            std::cout << "Goodbye!\n";
        } else {
            std::cout << "I don't understand that command.\n";
        }
    }

    return 0;
}