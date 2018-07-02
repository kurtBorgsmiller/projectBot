/* Kurt Borgsmiller
Southern Illinois University
 5 June 2018
 ICYPC Challenge Bot */

#include "const.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Child
{
	int x, y; // Map positioning
	bool position; // true if standing, false if crouched
	int color; // Team color
	int holding; // What the child is holding	
	int dazed; // Number of turns child is stunned for
};

// X and Y displacement for each walk direction 
int dispX[] = { 1, 0 , -1 , 0 };
int dispY[] = { 1, 0 , -1 , 0 };

// Walk direction for each child 
int walkDir[] = { 0 , 1, 2 , 3 };


// Current score 
int score[2];

// Snow height in each space 
vector <vector<int>> height(SIZE, vector<int>(SIZE));

// Contents of each space 
vector <vector<int>> ground(SIZE, vector<int>(SIZE));

// Update for each child's action
vector< Child > cList( CCOUNT * 2);



/*
Daze check) If child is dazed, must remain idle

1) If child is not holding anything, pick up snow

2) If child is holding a pile of snow, make it into a snowball

3) If child is holding a snowball, check if nearby enemies and throw if they are close enough
*/

bool makeMoveHunter(int i)
{
	Child &child = cList[i];
	
	if (child.dazed > 0) // Daze Check
	{
		cout << "idle" << endl;
		return true;
	}

	if (child.holding == HOLD_EMPTY) // 1) If child is not holding anything, pick up snow
	{
		int sx = -1, sy = -1;
		for (int ox = child.x - 1; ox <= child.x + 1; ox++)
		{
			for (int oy = child.y - 1; oy <= child.y + 1; oy++)
			{
				if (ox >= 0 && ox < FORT_SIZE &&
					oy >= 0 && oy < FORT_SIZE &&
					(ox != child.x || oy != child.y) &&
					ground[ox][oy] == GROUND_EMPTY &&
					height[ox][oy] > 0)
				{
					sx = ox;
					sy = oy;
				}
			}
		}
		if (sx >= 0)
		{
			if (child.position)
			{
				cout << "crouch" << endl;
				return true;
			}

			cout << "pickup " << sx << " " << sy << endl;
			ground[sx][sy] = GROUND_TAKEN;
			return true;
		}
	}

	if (child.holding == (HOLD_P1 || HOLD_P2 || HOLD_P3)) // 2) If child is holding a pile of snow, make it into a snowball
	{
		cout << "crush" << endl;
		return true;
	}

	if (child.holding == HOLD_S1 || HOLD_S2 || HOLD_S3) // 3) If child is holding a snowball, check if nearby enemies and throw if they are close enough
	{
		if (!child.position) // Stand if crouching
		{
			cout << "stand" << endl;
			return true;
		}

		for (int j = CCOUNT; j < CCOUNT + 2; j++)
		{
			int dx = cList[j].x - child.x;
			int dy = cList[j].y - child.y;
			int dsq = dx * dx + dy * dy;

			if (dsq < 8 * 8)
			{
				cout << "throw " << child.x + dx * 2 << " "
					<< child.y + dy * 2 << endl;
				return true;
			}
		}
	}
}


/*
4) If a child is holding a snowball and there are no enemies, look for nearby snowman to build on

5) If there is no snowman nearby, build one to expand the player's territory

6) If there is a snowman nearby, move to a new position away from the snowman
*/

bool makeMoveBuilder(int i)
{
	Child &child = cList[i];
	int snowmanCheck = 0;

	if (child.dazed > 0) // Daze Check
	{
		cout << "idle" << endl;
		return true;
	}

	if (child.holding == HOLD_EMPTY) // 1) If child is not holding anything, pick up snow
	{
		int sx = -1, sy = -1;
		for (int ox = child.x - 1; ox <= child.x + 1; ox++)
		{
			for (int oy = child.y - 1; oy <= child.y + 1; oy++)
			{
				if (ox >= 0 && ox < FORT_SIZE &&
					oy >= 0 && oy < FORT_SIZE &&
					(ox != child.x || oy != child.y) &&
					ground[ox][oy] == GROUND_EMPTY &&
					height[ox][oy] > 0)
				{
					sx = ox;
					sy = oy;
				}
			}
		}
		if (sx >= 0)
		{
			if (child.position)
			{
				cout << "crouch" << endl;
				return true;
			}

			cout << "pickup " << sx << " " << sy << endl;
			ground[sx][sy] = GROUND_TAKEN;
			return true;
		}
	}

	if (child.holding == HOLD_S1|| HOLD_S2 || HOLD_S3)
	{
		int dx = -1, dy = -1;
		for (int ox = child.x - 1; ox <= child.x + 3; ox++)
		{
			for (int oy = child.y - 1; oy <= child.y + 3; oy++)
			{
				if (ground[ox][oy] == GROUND_SMB || GROUND_SMR)
				{
					snowmanCheck = 1;
				}

				if (ground[ox][oy] == GROUND_M && snowmanCheck != 1 && height[ox][oy] < OBSTACLE_HEIGHT 
					&& ground[ox][oy] != GROUND_TREE)
				{
					dx = ox;
					dy = oy;

					cout << "drop " << dx << " " << dy << endl;
					return true;
				}


				
			}
		}


		if (snowmanCheck == 1)
		{
			int newX = child.x + dispX[walkDir[i]];
			int newY = child.y + dispY[walkDir[i]];
			
			cout << "run " << newX << " " << newY << endl;
		}
		else
		{


			int sx = -1, sy = -1;
			for (int ox = child.x - 1; ox <= child.x + 1; ox++)
			{
				for (int oy = child.y - 1; oy <= child.y + 1; oy++)
				{
					if (ox >= 0 && ox < FORT_SIZE &&
						oy >= 0 && oy < FORT_SIZE &&
						(ox != child.x || oy != child.y) &&
						ground[ox][oy] == GROUND_EMPTY &&
						height[ox][oy] > 0)
					{
						sx = ox;
						sy = oy;
					}
				}
			}
			if (sx >= 0)
			{
				if (child.position)
				{
					cout << "crouch" << endl;
					return true;
				}

				cout << "pickup " << sx << " " << sy << endl;
				ground[sx][sy] = GROUND_TAKEN;
				return true;
			}
		}
	}

	if (child.holding == HOLD_M)
	{
		int dx = -1, dy = -1;
		for (int ox = child.x - 1; ox <= child.x + 3; ox++)
		{
			for (int oy = child.y - 1; oy <= child.y + 3; oy++)
			{
				if (ground[ox][oy] == GROUND_SMB || GROUND_SMR)
				{
					snowmanCheck = 1;
				}

				if (ground[ox][oy] == GROUND_L && snowmanCheck != 1)
				{
					dx = ox;
					dy = oy;

					cout << "drop " << dx << " " << dy << endl;
					return true;
				}
			}
		}

		if (snowmanCheck == 1)
		{
			int newX = child.x + dispX[walkDir[i]];
			int newY = child.y + dispY[walkDir[i]];

			cout << "run " << newX << " " << newY << endl;
		}
		else
		{
			int sx = -1, sy = -1;
			for (int ox = child.x - 1; ox <= child.x + 1; ox++)
			{
				for (int oy = child.y - 1; oy <= child.y + 1; oy++)
				{
					if (ox >= 0 && ox < FORT_SIZE &&
						oy >= 0 && oy < FORT_SIZE &&
						(ox != child.x || oy != child.y) &&
						ground[ox][oy] == GROUND_EMPTY &&
						height[ox][oy] > 0)
					{
						sx = ox;
						sy = oy;
					}
				}
			}
			if (sx >= 0)
			{
				if (child.position)
				{
					cout << "crouch" << endl;
					return true;
				}

				cout << "pickup " << sx << " " << sy << endl;
				ground[sx][sy] = GROUND_TAKEN;
				return true;
			}
		}
	}

	if (child.holding == HOLD_L)
	{
		int dx = -1, dy = -1;
		for (int ox = child.x - 1; ox <= child.x + 3; ox++)
		{
			for (int oy = child.y - 1; oy <= child.y + 3; oy++)
			{
				if (ground[ox][oy] == GROUND_SMB || GROUND_SMR)
				{
					snowmanCheck = 1;
				}
				if (ground[ox][oy] == GROUND_EMPTY && snowmanCheck != 1)
				{
					dx = ox;
					dy = oy;

					cout << "drop " << dx << " " << dy << endl;
					return true;
				}
			}
		}

		if (snowmanCheck == 1)
		{
			int newX = child.x + dispX[walkDir[i]];
			int newY = child.y + dispY[walkDir[i]];

			cout << "run " << newX << " " << newY << endl;
		}
		else
		{
			int sx = -1, sy = -1;
			for (int ox = child.x - 1; ox <= child.x + 1; ox++)
			{
				for (int oy = child.y - 1; oy <= child.y + 1; oy++)
				{
					if (ox >= 0 && ox < FORT_SIZE &&
						oy >= 0 && oy < FORT_SIZE &&
						(ox != child.x || oy != child.y) &&
						ground[ox][oy] == GROUND_EMPTY &&
						height[ox][oy] > 0)
					{
						sx = ox;
						sy = oy;
					}
				}
			}
			if (sx >= 0)
			{
				if (child.position)
				{
					cout << "crouch" << endl;
					return true;
				}

				cout << "pickup " << sx << " " << sy << endl;
				ground[sx][sy] = GROUND_TAKEN;
				return true;
			}
		}
	}

	if (child.holding == (HOLD_P1 || HOLD_P2 || HOLD_P3)) // 2) If child is holding a pile of snow, make it into a snowball
	{
		cout << "crush" << endl;
		return true;
	}
}



int main() {
	int turnNum;
	cin >> turnNum;
	while (turnNum >= 0) {
		// Read the current score.
		cin >> score[RED] >> score[BLUE];

		// Read the state of the field.
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++) {
				char a, b;
				cin >> a >> b;
				if (a != '*') {
					height[i][j] = a - '0';
					ground[i][j] = b - 'a';
				}
				else {
					height[i][j] = -1;
					ground[i][j] = -1;
				}
			}

		string token;
		for (int i = 0; i < cList.size(); i++) {
			cin >> token;
			if (token == "*") {
				// Can't see this child
				cList[i].x = -1;
				cList[i].y = -1;
			}
			else {
				// Can see this child, read the description.
				cList[i].x = atoi(token.c_str());
				cin >> cList[i].y;

				// Fill in the child's side.
				cList[i].color = i / CCOUNT;

				// Read the child's stanse, what he's holding and how much
				// longer he's dazed.
				char ch;
				cin >> ch;
				cList[i].position = (ch == 'S');
				cin >> ch;
				cList[i].holding = (ch - 'a');
				cin >> cList[i].dazed;
			}
		}

		// Mark child locations, so we can walk around them.
		for (int i = 0; i < cList.size(); i++) {
			if (cList[i].x >= 0) {
				ground[cList[i].x][cList[i].y] = GROUND_CHILD;
			}
		}

		// Choose an action for each child.
		for (int i = 0; i < CCOUNT - 2; i++) {
			// Try up to three times to get a useful move
			int tryCount = 0;

			while (tryCount < 3 &&
				!makeMoveHunter(i))
				tryCount++;

			// If we can't think of a good move, wait and see if something happens.
			if (tryCount >= 3)
				cout << "idle" << endl;
		}

		for (int i = 2; i < CCOUNT; i++) {
			// Try up to three times to get a useful move
			int tryCount = 0;

			while (tryCount < 3 &&
				!makeMoveBuilder(i))
				tryCount++;

			// If we can't think of a good move, wait and see if something happens.
			if (tryCount >= 3)
				cout << "idle" << endl;
		}

		cin >> turnNum;
	}
}
