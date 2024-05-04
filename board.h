#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <random>
#include "ship.h"
using namespace std;

// constants for size of the game board
const int rows = 10;
const int cols = 10;

class board {
private:
	string gameBoard[rows][cols] = {};
	string guessBoard[rows][cols] = {};
	int spotsTaken[rows][cols] = {};

	// How many the computer and player starts with
	int numPlyrShips = 5;
	int numCompShips = 5;

	// Define the ships
	ship carrier = { "Carrier", 5, 0, 0, 'h', 0, false };
	ship battleship = { "Battleship", 4, 0, 0, 'h', 0, false };
	ship destroyer = { "Destroyer", 3, 0, 0, 'h', 0, false };
	ship submarine = { "Submarine", 3, 0, 0, 'h', 0, false };
	ship cruiser = { "Cruiser", 2, 0, 0, 'h', 0, false };

	// All the ships
	ship ships[5] = { carrier, battleship, destroyer, submarine, cruiser };

	// move the ship up on the grid
	void up(int row, int col, int length, char orientation) {

		if (row == 0) { // cant move up if you're at the top row, for either orientation
			return;
		}

		if (orientation == 'h') { // horizontal

			int newLength = length + col; // length of the ship from its starting col, used in for loops

			for (int i = col; i < newLength; i++) { // delete old horizontal ship
				gameBoard[row][i] = "";
			}

			int newRow = row - 1; // decrement row to display "moving up"

			for (int i = col; i < newLength; i++) { // draw new horizontal ship
				gameBoard[newRow][i] = " S ";
			}
		}
		else { // vertical

			int newLength = length + row; // length of the ship from its starting row, used in for loops

			for (int i = row; i < newLength; i++) { // delete old vertical ship
				gameBoard[i][col] = "";
			}
			
			int newRow = row - 1; // decrement row to display "moving up"

			newLength--; // modify the new length to correctly display the ship "moving up"

			for (int i = newRow; i < newLength; i++) { // Draw new vertical ship
				gameBoard[i][col] = " S ";
			}
		}
	}

	// move the ship down on the grid
	void down(int row, int col, int length, char orientation) {

		if (orientation == 'h') { // horizontal

			if (row == 9) { // cant move down if row is the last row, and the ship is horizontal
				return;
			}

			int newLength = length + col; // length of the ship from its starting col, used in for loops

			for (int i = col; i < newLength; i++) { // Delete old horizontal ship
				gameBoard[row][i] = "";
			}

			int newRow = row + 1; // increment row to display " moving down"

			for (int i = col; i < newLength; i++) { // Draws new horizontal ship
				gameBoard[newRow][i] = " S ";
			}
		}
		else { // vertical

			int newLength = length + row; // length of the ship from its starting row, used in for loops

			if ((newLength - 10) == 0) { // Cant go down if start row = 5 and ship is vertical 
				return;
			}

			for (int i = row; i < newLength; i++) { // Delete old vertical ship
				gameBoard[i][col] = "";
			}

			int newRow = row + 1; // increment row to display " moving down"

			newLength++; // modify the new length to correctly display the ship "moving down"

			for (int i = newRow; i < newLength; i++) { // Draw new vertical ship
				gameBoard[i][col] = " S ";
			}
		}
	}

	// move the ship left on the grid
	void left(int row, int col, int length, char orientation) {
		
		if (col == 0) { // Cant go left if leftmost column, for either orientation
			return;
		}

		if (orientation == 'h') { // horizontal

			int newLength = length + col; // length of the ship from its starting col, used in for loops

			for (int i = col; i < newLength; i++) { // Delete old horizontal ship
				gameBoard[row][i] = "";
			}
			
			int newCol = col - 1; // decrement the col to display "moving left"

			newLength--; // modify the new length to correctly display the ship "moving left"

			for (int i = newCol; i < newLength; i++) { // Draw new horizontal ship
				gameBoard[row][i] = " S ";
			}
		}
		else { // vertical

			int newLength = length + row; // length of the ship from its starting row, used in for loops

			for (int i = row; i < newLength; i++) { // Delete old vertical ship
				gameBoard[i][col] = "";
			}

			int newCol = col - 1; // decrement the col to display "moving left"
			
			for (int i = row; i < newLength; i++) { // Draw new vertical ship
				gameBoard[i][newCol] = " S ";
			}
		}
	}

	// move the ship left on the grid
	void right(int row, int col, int length, char orientation) {

		if (orientation == 'h') { // horizontal

			int newLength = length + col; // length of the ship from its starting col, used in for loops

			if ((newLength - 10) == 0) { // Cant move right if horizontal
				return;
			}

			for (int i = col; i < newLength; i++) { // Delete old horizontal ship
				gameBoard[row][i] = "";
			}

			int newCol = col + 1; // increment col to display "moving right"

			newLength++; // modify the new length to correctly display the ship "moving left"

			for (int i = newCol; i < newLength; i++) { // Draw new horizontal ship
				gameBoard[row][i] = " S ";
			}
		}
		else { // vertical

			if (col == 9) { // Cant go right if ship is in last col and is vertical
				return;
			}

			int newLength = length + row; // length of the ship from its starting row, used in for loops

			for (int i = row; i < newLength; i++) { // Delete old vertical ship
				gameBoard[i][col] = "";
			}

			int newCol = col + 1; // increment the col to display "moving right"

			for (int i = row; i < newLength; i++) { // Draw new vertical ship
				gameBoard[i][newCol] = " S ";
			}
		}
	}

public:

	// default constructor
	board() {}

	// default destructor
	~board() {}

	// displays game board
	void displayBoard() {
		char ascii = 'A';
		cout << "   Ship Board                               \n";
		cout << "     1   2   3   4   5   6   7   8   9   10 \n";
		cout << "   -----------------------------------------\n";
		for (int i = 0; i < rows; i++) {

			// players gameboard
			cout << " " << ascii << " |";
			for (int j = 0; j < cols; j++) {
				if (gameBoard[i][j] == "") {
					cout << "   |";
				}
				else {
					cout << "" << gameBoard[i][j] << "|";
				}
			}
			cout << "\n   -----------------------------------------\n";
			ascii++;
		}

		// displays spots taken
		/*for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cout << spotsTaken[i][j] << " ";
			}
			cout << endl;
		}*/
	}

	// resets game
	void resetGame() {

		// reset all boards
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				gameBoard[i][j] = "";
				guessBoard[i][j] = "";
				spotsTaken[i][j] = 0;
			}
		}

		// reset the number of ships
		numPlyrShips = 5;
		numCompShips = 5;

		// reset ships
		for (int i = 0; i < 5; i++) {
			ships[i].resetShip();
		}
	}


	//// player functions

	// displays spots guessed by player
	void plyrGuessBoard() {
		char ascii = 'A';
		cout << "   Ship Board                                    Guess Board                              \n";
		cout << "     1   2   3   4   5   6   7   8   9   10        1   2   3   4   5   6   7   8   9   10 \n";
		cout << "   -----------------------------------------     -----------------------------------------\n";
		for (int i = 0; i < rows; i++) {

			// players gameboard
			cout << " " << ascii << " |";
			for (int j = 0; j < cols; j++) {
				if (gameBoard[i][j] == "") {
					cout << "   |";
				}
				else {
					cout << "" << gameBoard[i][j] << "|";
				}
			}

			// players guess board
			cout << "   " << ascii << " |";
			for (int j = 0; j < cols; j++) {
				if (guessBoard[i][j] == "") {
					cout << "   |";
				}
				else {
					cout << "" << guessBoard[i][j] << "|";
				}
			}

			// some ship info


			cout << "\n   -----------------------------------------     -----------------------------------------\n";
			ascii++;
		}
	}

	// places player ships on the gameboard
	void placePlyrShips() {

		for (int i = 0; i < 5; i++) { // For each ship
			ship s = ships[i];

			// gets some ship details from the input ship
			int length = s.getLength();
			int startRow = s.getStartRow();
			int startCol = s.getStartCol();

			// find an empty horizontal spot to put the ship /////// still needs work
			bool placed = false;

			for (int i = 0; i < 10; i++) { // for each row of the game board

				for (int j = 0; j < 10; j++) { // for each col of the game board

					if (((j + length) - 10) < 0) { // if the ship isn't all the way right

						int newLength = length + i; // adjust the length for the for loops

						int count = 0; // counts number of open spaces

						for (int s = j; s < newLength; s++) { // for the length of the ship currently being placed

							if (spotsTaken[i][s] == true) { // if a spot is taken, break
								break;
							}
							else {
								count++; // increments the number of open spots
							}
						}

						if (count == length) { // if we found a spot to put the ship
							for (int i = startCol; i < newLength; i++) { // draw new horizontal ship
								gameBoard[startRow][i] = " S ";
								placed = true;
							}
						}
					}
					else {
						startCol = 0;
						break; // Exit loop so we aren't checking a spot that already cant be used
					}
					if (placed == true) {
						break;
					}
					startCol++;
				}
				if (placed == true) {
					break;
				}
				startRow++;
			}

			cout << "\n\nUse the arrow keys to move the ship around. Press 'v' or 'h' to change the ships orientation.\nOnce you are happy with your ships placement, press enter\n\nShip: " << s.getName() << "\n\n";
			displayBoard();

			// default orientation of for how the find empty spot works
			char orientation = 'h';

			bool placing = true;
			while (placing) { // Infinite loop
				int c = _getch(); // Read a character
				switch (c) {
				case 224: {// Arrow keys are preceded by a 224
					switch (_getch()) { // Now read the real value
					case 72: { // up

						cout << "\n\nUse the arrow keys to move the ship around. Press 'v' or 'h' to change the ships orientation.\nOnce you are happy with your ships placement, press enter\n\nShip: " << s.getName() << "\n\n";

						// Check to make sure we don't run into other ships that have already been placed
						if (orientation == 'h') { // horizontal

							int newLength = startCol + length; // modifies length to be from the starting col to the end of the ship

							int newRow = startRow - 1; // decrement the row to simulate the ship "moving up"

							int count = 0; // count that stores the number of spaces taken

							for (int i = startCol; i < newLength; i++) {
								if (spotsTaken[newRow][i] == 1) { // If any of the spots we are trying to move to is taken
									count++;
								}
								if (count > 0) { // if this spot is taken, stop searching in this spot
									break;
								}
							}

							if (count == 0) {
								// since the spot is available, move the ship
								up(startRow, startCol, length, orientation);

								if (startRow > 0) { // if the ship is at the top row you cant move up
									startRow--;
								}
							}

						}
						else { // vertical

							int top = startRow - 1; // simulate the top of the ship after "moving up"

							if (spotsTaken[top][startCol] == 1) { // if the spot is not available, break
								break;
							}
							else {
								// since the spot is available, move the ship
								up(startRow, startCol, length, orientation);

								if (startRow > 0) { // if the ship is at the top row you cant move up
									startRow--;
								}
							}

						}

						// display the updated position of the ship on the grid
						displayBoard();
						break;
					}
					case 80: { // down

						// Check to make sure we don't run into other ships that have already been placed
						if (orientation == 'h') { // horizontal

							int newLength = startCol + length; // modifies length to be from the starting col to the end of the ship

							int newRow = startRow + 1; // increment the row to simulate the ship "moving down"

							int count = 0; // count that stores the number of spaces taken

							for (int i = startCol; i < newLength; i++) {
								if (spotsTaken[newRow][i] == 1) { // If any of the spots we are trying to move to is taken
									count++;
								}
								if (count > 0) { // if this spot is taken, stop searching in this spot
									break;
								}
							}

							if (count == 0) {// since the spot is available, move the ship

								down(startRow, startCol, length, orientation);

								if (startRow < 9) { // If the ship is not at the bottom row, increase the row after moving
									startRow++;
								}
							}
						}
						else { // vertical

							int bottom = (startRow + 1) + (length - 1); // bottom of the ship after "moving down"

							if (spotsTaken[bottom][startCol] == 1) { // if the spot that the ship would move to is taken, break
								break;
							}
							else { // the spot is available

								// move the ship
								down(startRow, startCol, length, orientation);

								if (((startRow + length) - 10) != 0) { // if the bottom of the ship is not on the last row, increase the row after moving
									startRow++;
								}
							}
						}

						// display the updated position of the ship on the grid
						displayBoard();
						break;
					}
					case 75: { // left

						if (orientation == 'h') { // horizontal

							int newCol = startCol - 1; // decrement the col to simulate the ship "moving left"

							if (spotsTaken[startRow][newCol] == 1) { // if the spot that the ship would move to is taken, break
								break;
							}
							else {

								// since the spot is available, move the ship
								left(startRow, startCol, length, orientation);

								if (startCol > 0) {
									startCol--;
								}
							}
						}
						else { // vertical

							int newLength = startRow + length; // modifies length to be from the starting row to the end of the ship

							int newCol = startCol - 1; // decrement the row to simulate the ship "moving left"

							int count = 0; // count that stores the number of spaces taken

							for (int i = startRow; i < newLength; i++) {
								if (spotsTaken[i][newCol] == 1) { // If any of the spots we are trying to move to is taken
									count++;
								}
								if (count > 0) { // if this spot is taken, stop searching in this spot
									break;
								}
							}

							if (count == 0) { // if no spaces are taken

								// since the spot is available, move the ship
								left(startRow, startCol, length, orientation);

								if (startCol > 0) {
									startCol--;
								}
							}
						}
						// display the updated position of the ship on the grid
						displayBoard();
						break;
					}
					case 77: { // right

						if (orientation == 'h') { // horizontal

							int newCol = startCol + 1; // decrement the col to simulate the ship "moving right"

							if (spotsTaken[startRow][newCol] == 1) { // if the spot that the ship would move to is taken, break
								break;
							}
							else {

								// since the spot is available, move the ship
								right(startRow, startCol, length, orientation);

								if (((startCol + length) - 10) < 0) {
									startCol++;
								}
							}
						}
						else { // vertical

							int newLength = startRow + length; // modifies length to be from the starting row to the end of the ship

							int newCol = startCol + 1; // decrement the row to simulate the ship "moving right"

							int count = 0; // count that stores the number of spaces taken

							for (int i = startRow; i < newLength; i++) {
								if (spotsTaken[i][newCol] == 1) { // If any of the spots we are trying to move to is taken
									count++;
								}
								if (count > 0) { // if this spot is taken, stop searching in this spot
									break;
								}
							}

							if (count == 0) { // if no spaces are taken

								// move the ship
								right(startRow, startCol, length, orientation);

								if (startCol < 9) {
									startCol++;
								}
							}
						}

						// display the updated position of the ship on the grid
						displayBoard();
						break;
					}
					}
					break;
				}
				case 104: { // h is pressed, change orientation

					// check if orientation can be changed while around other ships
					int newLength = length + startCol;
					int count = 0;
					for (int i = startCol; i < newLength; i++) {
						if (spotsTaken[startRow][i] == 1) {
							count++;
						}
					}
					if (count == 0) {
						if (((startCol + length) - 10) > 0) { // if the ship cant change orientation
							break;
						}
						newLength = length + startRow;
						for (int i = startRow; i < newLength; i++) { // delete old vertical ship
							gameBoard[i][startCol] = "";
						}
						newLength = length + startCol;
						for (int i = startCol; i < newLength; i++) { // draw new horizontal ship
							gameBoard[startRow][i] = " S ";
						}
						// display the updated position of the ship on the grid
						displayBoard();
						orientation = 'h';
						count = 0;
					}
					break;
				}
				case 118: { // v is pressed

					// check if orientation can be changed while around other ships
					int newLength = length + startRow;
					int count = 0;
					for (int i = startRow; i < newLength; i++) {
						if (spotsTaken[i][startCol] == 1) {
							count++;
						}
					}
					if (count == 0) {
						if (((startRow + length) - 10) > 0) { // if the ship cant change orientation
							break;
						}
						newLength = length + startCol;
						for (int i = startCol; i < newLength; i++) { // delete old horizontal ship
							gameBoard[startRow][i] = "";
						}
						newLength = length + startRow;
						for (int i = startRow; i < newLength; i++) { // draw new vertical ship
							gameBoard[i][startCol] = " S ";
						}
						// display the updated position of the ship on the grid
						displayBoard();
						orientation = 'v';
						count = 0;
					}
					break;
				}
				case 13: { // Enter is pressed, player is done moving ship
					if (orientation == 'h') {

						int newLength = startCol + length;

						for (int i = startCol; i < newLength; i++) { // Lock in horizontal ship 
							spotsTaken[startRow][i] = 1;
						}
					}
					else {

						int newLength = startRow + length;

						for (int i = startRow; i < newLength; i++) { // Lock in vertical ship 
							spotsTaken[i][startCol] = 1;
						}
					}

					s.updateShip(startRow, startCol, orientation);

					cout << "\n";
					startRow = 0;
					startCol = 0;
					placing = false;
				}
				}
			}
		}
	}

	// attack the computer
	int attackComp(board computer) {

		// ship index that we will used to return the number of ships the computer has left
		int shipIndex = 0;
		
		bool attacking = true;
		while (attacking == true) {

			if (numCompShips == 0) {
				attacking = false;
			}

			// get the players coordinate guess
			string guess;
			cout << "Enter coordinates to fire at the computer (e.g. A6 E10 B4): ";
			cin >> guess;

			// checks for valid coordinates
			if (guess.length() < 3) {
				while ((guess[0] < 'A' || guess[0] > 'J') || (guess[1] < '1' || guess[1] > '9') || (guess.length() < 3)) {
					cout << "\nError: " << guess << " is an invalid input\n\n";
					cout << "Enter coordinates to fire at the computer (e.g. A6 E7 B4): ";
					cin >> guess;
				}
			}
			else {
				while ((guess[1] != '1' && guess[2] != '0') || (guess.length() > 3)) {
					cout << "\nError: " << guess << " is an invalid input\n\n";
					cout << "Enter coordinates to fire at the computer (e.g. A6 E7 B4): ";
					cin >> guess;
				}
			}

			// turns coordinates into integers
			int row = 0, col = 0;
			if (guess.length() < 3) {
				row = guess[0] - 'A';
				col = guess[1] - '1';
			}
			else {
				row = guess[0] - 'A';
				col = 9; // user sees 1-10 but the code logic uses 0-9
			}

			if (computer.spotsTaken[row][col] == true) { // if the spot guessed by the player "hits" one of the computers ships

				// some cool ascii art
				cout << endl;
				cout << "   ()    ()  ()()()()  ()()()()  ()\n";
				cout << "   ()    ()     ()        ()     ()\n";
				cout << "   ()()()()     ()        ()     ()\n";
				cout << "   ()    ()     ()        ()       \n";
				cout << "   ()    ()  ()()()()     ()     ()\n\n";

				// update the players guess board
				guessBoard[row][col] = " X ";

				// get the ship that was hit
				for (int i = 0; i < 5; i++) { // for each ship
					
					// will determine if we found the ship
					bool found = false;

					// gets the cords of the current ship we are checking
					string coords = computer.ships[i].getCoords();

					for (int j = 0; j < coords.length();) { // for each set of coordinates
						
						int r = j;     // row
						int c = j + 1; // col

						if ((coords[r] - '0') == row && (coords[c] - '0') == col) { // if the row and col that got hit is in this coordinate set
							
							// increase the number of hits to this ship
							computer.ships[i].hit(); // + 1 hit

							// check if the player has sunk the ship
							if (computer.ships[i].hasSunk() == true) {
								numCompShips = numCompShips - 1;

								// tell they player what ship they sunk
								cout << "  !!! You sunk the computers " << computer.ships[i].getName() << " !!!\n";

								// mark the ship on the board as all X's, and the space surrounding the ship
								for (int s = 0; s < coords.length();) {

									int startr = (coords[s] - '0');
									int startc = (coords[s+1] - '0');

									guessBoard[startr][startc] = " X ";

									s = s + 3;
								}

								// add logic to mark X's around the ship
							}

							// display the players guess board
							plyrGuessBoard();

							if (numCompShips == 0) {
								attacking = false;
							}

							shipIndex = i;

							found = true;
						}
						if (found == true) {
							break;
						}
						else {
							j = j + 3;
						}
					}
					if (found == true) {
						break;
					}
				}
			}
			else {

				// some cool ascii art
				cout << endl;
				cout << "   ())  (()  ()()()()  ()()()    ()()()   ()\n";
				cout << "   ()()()()     ()    ()_   ()  ()_   ()  ()\n";
				cout << "   () () ()     ()      ^()_      ^()_    ()\n";
				cout << "   ()    ()     ()    ()   ^()  ()   ^()    \n";
				cout << "   ()    ()  ()()()()  ()()()    ()()()   ()\n\n";

				// update the players guess board
				guessBoard[row][col] = " * ";

				// display the players guess board
				plyrGuessBoard();

				// stop the loop
				attacking = false;
			}
		}
		return numCompShips;
	}


	//// computer functions

	// places computers ships on their game board
	void placeCompShips() {

		for (int i = 0; i < 5; i++) { // for each ship

			ship s = ships[i]; // current ship

			int length = s.getLength(); // get length of the ship

			// Create a random device
			random_device rd;
			// Seed the generator
			mt19937 gen(rd());
			// Define the distribution range: 0 to 9 for random coordinates
			uniform_int_distribution<> distrib(0, 9);

			// Define the distribution range: 0 to 1 for random orientation
			uniform_int_distribution<> distrib2(0, 1);

			bool placed = false;
			while (placed == false) {

				char orientation = 'h'; // default orientation

				// Generate random starting coordinates
				int startRow = distrib(gen);
				int startCol = distrib(gen);
				int o = distrib2(gen);

				if (o != 0) {
					orientation = 'v'; // if o = 1 set orientation to vertical
				}

				// Find an empty horizontal spot to put the ship
				if (orientation == 'h') {

					if (((startCol + length) - 10) < 0) { // If the ships starting coordinates aren't too far right

						int newLength = length + startCol; // Adjust the length for the for loops

						int count = 0; // Counts number of open spaces

						for (int s = startCol; s < newLength; s++) { // For the length of the ship currently being placed
							if (spotsTaken[startRow][s] == 1) {

								break;
							}
							else {
								count++;
							}
						}

						if (count == length) { // We found a spot to put the ship
							for (int i = startCol; i < newLength; i++) { // Draw new horizontal ship
								gameBoard[startRow][i] = " S ";
								spotsTaken[startRow][i] = 1;
							}
							ships[i].updateShip(startRow, startCol, orientation); // update actual ship
							placed = true;
						}
					}
				}
				else { // vertical

					if (((startRow + length) - 10) < 0) { // If the ships starting coordinates aren't too far down

						int newLength = length + startRow; // Adjust the length for the for loops

						int count = 0; // Counts number of open spaces

						for (int s = startRow; s < newLength; s++) { // For the length of the ship currently being placed
							if (spotsTaken[s][startCol] == 1) {
								break;
							}
							else {
								count++;
							}
						}

						if (count == length) { // We found a spot to put the ship
							for (int i = startRow; i < newLength; i++) { // Draw new vertical ship
								gameBoard[i][startCol] = " S ";
								spotsTaken[i][startCol] = 1;
							}
							ships[i].updateShip(startRow, startCol, orientation); // update actual ship
							placed = true;
						}
					}
				}
			}
		}
	}

	// attack the player
	int attackPlyr(board player) {
		return 1;
	}
};