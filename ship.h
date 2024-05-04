#include <iostream>
#include <string>
using namespace std;

class ship {
private:
	string name = "";		// name of ship
	string coords = { "" }; // all coordinates of the ship
	int length = 0;			// length of the ship
	int startRow = 0;		// X-coordinate of the starting position
	int startCol = 0;		// Y-coordinate of the starting position
	int numHits = 0;		// count to store the number of times the ship has been hit
	int numShips = 5;		// count to store the number of ships standing
	char orientation = 'h'; // 'h' for horizontal, 'v' for vertical
	bool sunk = false;		// check for if the ship is sunk or not

public:

	// default constructor
	ship() {}

	// overloaded constructor
	ship(string s, int l, int startR, int startC, char o, int h, bool snk) {
		name = s;
		length = l;
		startRow = startR;
		startCol = startC;
		orientation = o;
		numHits = h;
		sunk = snk;
	}

	// gets ship name
	string getName() { return name; }

	// gets all coordinates of the ship
	string getCoords() {
		return coords;
	}

	// gets length of ship
	int getLength() { return length; }

	// gets starting row
	int getStartRow() { return startRow; }

	// gets starting col
	int getStartCol() { return startCol; }

	// gets number of ships standing
	int getNumShips() { return numShips; }

	// gets ships orientation
	char getOrientation() { return orientation; }

	// increments the number of times the ship has bene hit
	void hit() { numHits = numHits + 1; }

	// updates the start row, start col, orientation, and all coordinates of the ship 
	void updateShip(int row, int col, char o) {
		startRow = row;
		startCol = col;
		orientation = o;

		if (orientation == 'h') {
			for (int i = startCol; i < (length + startCol); i++) {
				coords.append(to_string(startRow));
				coords.append(to_string(i));
				coords.append(",");
			}
		}
		else {
			for (int i = startRow; i < (length + startRow); i++) {
				coords.append(to_string(i));
				coords.append(to_string(startCol));
				coords.append(",");
			}
		}
	}

	// determines if the ship has sunk
	bool hasSunk() {
		if (numHits == length) {
			sunk = true;
			numShips = numShips - 1;
			return sunk;
		}
		return sunk;
	}

	// resets ship 
	void resetShip() {
		coords = "";
		startRow = 0;
		startCol = 0;
		numHits = 0;
		numShips = 5;
		orientation = 'h';
		sunk = false;
	}
};