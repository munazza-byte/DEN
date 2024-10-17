#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>  // for random number generation
#include <ctime>    // to seed the random number generator

// Global Variables
std::vector<std::string> inventory; // To store player items
int playerHP = 100;
int playerStrength = 50; // Strength affects player's ability to fight or move objects
int playerDamage = 10;   // Base damage dealt by the player

// Function Declarations
void startGame();
void forest();
void cave();
void river();
void treasure();
void village();
void mountains();
void checkInventory();
void combat(std::string enemy, int enemyHP, int enemyDamage);
bool useItem();
void puzzleChallenge1();
void puzzleChallenge();
void endGame(std::string outcome);
void playAgain();
int getUserChoice(int numChoices);

// Main Function
int main() {
	std::srand(std::time(0));  // Seed the random number generator
	startGame();

	return 0;
}

// Function Definitions

void startGame() {
	playerHP = 100; // Reset HP at the beginning of the game
	playerStrength = 50; // Reset Strength
	playerDamage = 10;   // Reset base damage
	std::cout << "Welcome to the Text-Based Adventure Game!\n";
	std::cout << "You wake up in a dark forest with 100 HP and 50 Strength. You don't know where you are.\n";
	forest(); // Start the adventure
}

void forest() {
	std::cout << "\nYou are standing in a dense forest. There are paths to the north, east, south and west.\n";
	std::cout << "1. Go north (to the cave)\n";
	std::cout << "2. Go east (to the river)\n";
	std::cout << "3. Go west (to the village)\n";
	std::cout << "4. Go south (to the mountains)\n";
	std::cout << "5. Seek Treasure \n";
	std::cout << "6. Use Item\n";
	std::cout << "7. Combat\n";
	std::cout << "8. Check Inventory\n";
	std::cout << "9. EXIT\n";
	std::cout << "Choose an action: ";


	int choice = getUserChoice(9);

	switch (choice) {
	case 1:
		cave();
		forest();
		break;
	case 2:
		river();
		forest();
		break;
	case 3:
		village();
		forest();
		break;
	case 4:
		mountains();
		forest();
		break;
	case 5:
		treasure();
		forest();
		break;
	case 6:
		useItem();
		forest();
		break;
	case 7:
		combat("Goblin", 40, 5);
		forest();
		break;
	case 8:
		checkInventory();
		forest();
		break;
	case 9:
		exit(0);
	default:
		std::cout << "Invalid choice. Try again.\n";
		forest();
		break;
	}
}


void cave() {
	std::cout << "\nYou arrive at the entrance of a dark cave.\n";
	std::cout << "1. Enter the cave\n";
	std::cout << "2. Go back to the forest\n";
	std::cout << "Choose an action: ";

	int choice = getUserChoice(2);

	switch (choice) {
	case 1:
		std::cout << "You bravely enter the cave and find a hidden treasure!\n";
		inventory.push_back("Gold Coin");
		endGame("win");
		break;
	case 2:
		forest();
		break;
	default:
		std::cout << "Invalid choice. Try again.\n";
		cave();
		break;
		playAgain();
	}
}

void river() {
	std::cout << "\nYou reach a fast-flowing river. There is no bridge.\n";
	std::cout << "1. Try to swim across (-20 HP)\n";
	std::cout << "2. Go back to the forest\n";
	std::cout << "Choose an action: ";

	int choice = getUserChoice(2);

	switch (choice) {
	case 1:
		playerHP -= 20;
		if (playerHP > 0) {
			std::cout << "The current is strong, but you make it across. Your HP is now " << playerHP << ".\n";

			// Call the puzzle challenge before adding the jewel
			puzzleChallenge1();

			// Assume puzzleChallenge1 might lead to a lose condition, so check HP again
			if (playerHP > 0) {  // Ensure player is still alive after the puzzle
				inventory.push_back("Jewel"); // Add jewel to inventory
				std::cout << "You found a precious Jewel!\n";
			}
		}
		else {
			endGame("lose");
		}
		break;
	case 2:
		forest();
		break;
	default:
		std::cout << "Invalid choice. Try again.\n";
		river();
		break;
	}
	playAgain();
}




void village() {
	std::cout << "\nYou reach a quiet village. A villager offers you a sword if you can lift a heavy stone.\n";
	std::cout << "1. Try to lift the stone (requires 40 Strength)\n";
	std::cout << "2. Go back to the forest\n";
	std::cout << "Choose an action: ";

	int choice = getUserChoice(2);

	switch (choice) {
	case 1:
		if (playerStrength >= 40) {
			std::cout << "You lift the stone with your strength and the villager rewards you with a sword!\n";
			inventory.push_back("Sword");
			std::cout << "Your Strength is now " << (playerStrength -= 10) << ".\n";
		} else {
			std::cout << "You are not strong enough to lift the stone.\n";
		}
		playAgain();
		break;
	case 2:
		forest();
		break;
	default:
		std::cout << "Invalid choice. Try again.\n";
		village();
		break;
	}


}

void mountains() {
	std::cout << "\nYou arrive at the base of a tall mountain. Climbing it will be tough.\n";
	std::cout << "1. Climb the mountain (-30 Strength)\n";
	std::cout << "2. Go back to the forest\n";
	std::cout << "Choose an action: ";

	int choice = getUserChoice(2);

	switch (choice) {
	case 1:
		playerStrength -= 30;
		if (playerStrength > 0) {
			std::cout << "You manage to climb the mountain, and at the top you find a magical staff!\n";
			inventory.push_back("Magical Staff");
			endGame("win");
		}
		else {
			std::cout << "You collapse from exhaustion while climbing the mountain.\n";
			endGame("lose");
		}
		break;
	case 2:
		forest();
		break;
	default:
		std::cout << "Invalid choice. Try again.\n";
		mountains();
		break;
	}
	playAgain();
}


void treasure() {
	std::cout << "\nYou find a treasure chest on the other side of the river!\n";
	std::cout << "1. Open the chest\n";
	std::cout << "2. Ignore the chest\n";
	std::cout << "Choose an action: ";

	int choice = getUserChoice(2);

	switch (choice) {
	case 1:
		inventory.push_back("Jewel");
		std::cout << "You found a precious Jewel!\n";
		puzzleChallenge();  // New puzzle challenge after opening the treasure
		playAgain();
		break;
	case 2:
		std::cout << "You walk away from the treasure.\n";
		endGame("win");
		break;
	default:
		std::cout << "Invalid choice. Try again.\n";
		treasure();
		break;
	}
}

void checkInventory()
{
	std::cout << "Inventory: ";
	if (inventory.empty()) {
		std::cout << "Your inventory is empty.\n";
	}
	else
	{
		for (const auto &item : inventory)
		{
			std::cout << item << "\n";
		}
		std::cout << "\n";
	}
}

bool useItem() {
	std::cout << "\nDo you want to use an item? (yes/no): ";
	std::string choice;
	std::cin >> choice;

	if (choice == "yes") {
		if (inventory.size() > 0) {
			std::cout << "Select an item to use:\n";
			for (size_t i = 0; i < inventory.size(); ++i) {
				std::cout << (i + 1) << ". " << inventory[i] << "\n";
			}

			int itemChoice = getUserChoice(inventory.size());
			std::string selectedItem = inventory[itemChoice - 1];

			if (selectedItem == "Sword") {
				std::cout << "=======You wield the Sword to prepare for battle!========\n";
				playerDamage += 10;
			}
			else if (selectedItem == "Gold Coin")
			{
				std::cout<<"=======You use the Gold Coin to bribe a villager!=======";
			}
			else if (selectedItem == "Magical Staff") {
				std::cout << "=======You use the Magical Staff! You heal for 30 HP!========.\n";
				playerHP += 20;  // Heal with the staff
			} else if (selectedItem == "Jewel") {
				std::cout << "=======You sell the Jewel for a lot of money!=======\n";
			}

			// After using, remove the item
			inventory.erase(inventory.begin() + (itemChoice - 1));
			return true;
			playAgain();
		}
		else
		{
			std::cout<<"YOU DON'T HAVE EMOUGH ITEMS IN THE INVENTORY.\n";
		}

	}

	return false;
}

void combat(std::string enemy, int enemyHP, int enemyDamage) {
	while (enemyHP > 0 && playerHP > 0) {
		std::cout << "\nYou attack the " << enemy << " for " << playerDamage << " damage.\n";
		enemyHP -= playerDamage;
		if (enemyHP <= 0) {
			std::cout << "You defeated the " << enemy << "!\n";
			break;
		}

		std::cout << "The " << enemy << " attacks you for " << enemyDamage << " damage.\n";
		playerHP -= enemyDamage;
		std::cout << "Your HP is now " << playerHP << ".\n";

		if (playerHP <= 0) {
			endGame("lose");
			return;
		}
	}
	playAgain();
}

void puzzleChallenge1() {
	std::cout << "\nYou encounter a magical puzzle! Solve it to continue.\n";
	std::cout << "What is 7 + 5? ";

	int answer;
	std::cin >> answer;

	if (answer == 12) {
		std::cout << "Correct! You may proceed!\n";
		endGame("win");
	} else {
		std::cout << "Wrong answer! You are trapped!\n";
		endGame("lose");
	}
}

void puzzleChallenge() {
	std::cout << "\nYou encounter a mysterious door with a complex mechanism. You must solve a puzzle to pass.\n";
	std::cout << "1. Solve the puzzle (requires quick thinking)\n";
	std::cout << "2. Leave the puzzle unsolved and return\n";
	std::cout << "Choose an action: ";

	int choice = getUserChoice(2);

	if (choice == 1) {
		int puzzleAnswer = std::rand() % 2; // 50% chance of solving the puzzle
		if (puzzleAnswer == 1) {
			std::cout << "You solved the puzzle and move forward!\n";
			endGame("win");
		} else {
			std::cout << "You failed to solve the puzzle and are trapped.\n";
			endGame("lose");
		}
	}
	else {
		forest();
	}
	playAgain();

}


void endGame(std::string outcome) {
	if (outcome == "win") {
		std::cout << "\nCongratulations! You won the game!\n";
		std::cout << "Items collected: ";
		for (const auto &item : inventory) {
			std::cout << item << "\n";
		}
		std::cout << "\n";
	} else if (outcome == "lose") {
		std::cout << "\nYou lost the game. Better luck next time!\n";
	}
	playAgain();
}

void playAgain() {
	std::string choice;
	std::cout << "\nWould you like to play again? (yes/no): ";
	std::cin >> choice;

	if (choice == "yes") {
		startGame();
	} else if (choice == "no") {
		std::cout << "Thanks for playing!\n";
	} else {
		std::cout << "Invalid choice. Try again.\n";
		playAgain();
	}
}

// Function to validate user input for choices
int getUserChoice(int numChoices) {
	int choice;
	while (!(std::cin >> choice) || choice < 1 || choice > numChoices) {
		std::cout << "Invalid input. Please enter a number between 1 and " << numChoices << ": ";
		std::cin.clear();
		std::cin.ignore(10000, '\n');
	}
	return choice;
}
