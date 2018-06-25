/* Kurt Borgsmiller
Southern Illinois University
 5 June 2018
 ICYPC Challenge Bot */

#include "const.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

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

bool makeMove(int i)
{
	Child &child = cList[i];

	if (child.dazed > 0) // If Child is stunned must be idle 
	{
		cout << "idle" << endl;
		return true;
	}

	if (child.holding == HOLD_EMPTY) // If child is holding nothing then pick up snow
	{
		int sx = -1, sy = -1;
		for (int ox = child.x - 1; ox <= child.x + 1; ox++)
		{
			for (int oy = child.y - 1; oy <= child.y - 1; oy++)
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

	if (child.holding == (HOLD_P1 || HOLD_P2 || HOLD_P3)) // If child is holding any pile of snow, make a snowball
	{
		cout << "crush" << endl;
		return true;
	}

	if (child.holding == HOLD_S1) // If child is holding snowball
	{
		if (!child.position) // Stand if crouching
		{
			cout << "stand" << endl;
			return true;
		}

		for (int j = CCOUNT; j < CCOUNT * 2; j++)
		{
			if (cList[j].x >= 0)
			{
				int dx = cList[j].x - child.x;
				int dy = cList[j].y - child.y;
				int dsq = dx * dx + dy * dy;

				if (dsq < 8 * 8) // If enemy child is nearby, throw a snowball at them
				{
					cout << "throw " << child.x + dx * 2 << " "
						<< child.y + dy * 2 << endl;
					return true;
				}
			}
		}
	}
}
