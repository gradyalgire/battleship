#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include "board.h"

using namespace std;

int main() {

	bool playing = true;
	while (playing == true) {

		// define boards for both the player and the computer
		board player;
		board computer;

		cout << "()()())   (()())  ()()()() ()()()() ()     ()()()()    ()()()  ()    () ()()() ()()()  \n";
		cout << "()    () ()    ()    ()       ()    ()     ()         ()_   () ()    ()   ()   ()   () \n";
		cout << "()()())  ()()()()    ()       ()    ()     ()()()       ^()_   ()()()()   ()   ()()()  \n";
		cout << "()    () ()    ()    ()       ()    ()     ()         ()   ^() ()    ()   ()   ()      \n";
		cout << "()()())  ()    ()    ()       ()    ()()() ()()()()    ()()()  ()    () ()()() ()    By: Grady Algire\n\n";

		cout << "loading...\n";
		//this_thread::sleep_for(chrono::seconds(3));

		// Add ships to the users board
		player.placePlyrShips();
		cout << "\n\n\n\n\n\n\n";

		// Add computer ships to its board
		computer.placeCompShips();

		// each player starts with 5 ships
		int plyrShips = 5;
		int compShips = 5;

		while (plyrShips > 0 && compShips > 0) { // run until one of the players has no ships left
			
			// player attacks computer
			player.plyrGuessBoard();
			compShips = player.attackComp(computer);

			// computer attacks player

			//pause for computer "thinking" time
			cout << "Computer is guessing...";
			//this_thread::sleep_for(chrono::seconds(5));

			// attack
			plyrShips = computer.attackPlyr(player);
		}

		if (compShips == 0) {
			cout << endl;
			cout << "()    ()   ()()()   ()    ()     ()            ()  ()()()   ())   ()   ()\n";
			cout << " ()  ()   ()    ()  ()    ()      ()    ()    ()  ()    ()  ()()  ()   ()\n";
			cout << "   ()     ()    ()  ()    ()       ()  ()()  ()   ()    ()  () () ()   ()\n";
			cout << "   ()     ()    ()  ()    ()        ()()  ()()    ()    ()  ()  ()()     \n";
			cout << "   ()      ()()()    ()()()          ()    ()      ()()()   ()   (()   ()\n\n";
		}
		else {
			cout << endl;
			cout << "()    ()   ()()()   ()    ()     ()         ()()()    ()()()   ()()()()\n";
			cout << " ()  ()   ()    ()  ()    ()     ()        ()    ()  ()_   ()     ()   \n";
			cout << "   ()     ()    ()  ()    ()     ()        ()    ()    ^()_       ()   \n";
			cout << "   ()     ()    ()  ()    ()     ()        ()    ()  ()   ^()     ()   \n";
			cout << "   ()      ()()()    ()()()      ()()()()   ()()()    ()()()      ()   \n\n";
		}

		// prompt the user to play again
		char choice;
		cout << "Would you like to play again? (y/n): ";
		cin >> choice;

		// check to make sure the user entered only yes or no
		while ((choice != 'y' && choice != 'Y') && (choice != 'n' && choice != 'N')) {
			cout << "\nError: " << choice << " is an invalid input\n\n";
			cout << "Would you like to play again? (y/n): ";
			cin >> choice;
		}

		if (choice == 'y' || choice == 'Y') {
			player.resetGame();
			computer.resetGame();
		}
		else {
			cout << "\nThanks for playing!\n\nQuitting...";
			playing = false;
		}
	}
}