/* Kurt Borgsmiller
 Southern Illinois University
 5 June 2018
 Constants for ICYPC Challenge */

// Size of playing field 
const int SIZE = 31;

// Players per team 
const int CCOUNT = 4;

// Constants for ground objects 
const int GROUND_EMPTY = 0;
const int GROUND_TREE = 1;
const int GROUND_S = 2;
const int GROUND_M = 3;
const int GROUND_MS = 4;
const int GROUND_L = 5;
const int GROUND_LM = 6;
const int GROUND_LS = 7;
const int GROUND_SMR = 8;
const int GROUND_SMB = 9;
const int GROUND_CHILD = 10;
const int GROUND_TAKEN = 11;

// Constants for player inventory 
const int HOLD_EMPTY = 0;
const int HOLD_P1 = 1;
const int HOLD_P2 = 2;
const int HOLD_P3 = 3;
const int HOLD_S1 = 4;
const int HOLD_S2 = 5;
const int HOLD_S3 = 6;
const int HOLD_M = 7;
const int HOLD_L = 8;

// Constants for Red team (self) and Blue team (Opponent) 
const int RED = 0;
const int BLUE = 1;

// Height of Child's position 
const int STANDING_HEIGHT = 9; 
const int CROUCHING_HEIGHT = 6;

// Max Euclidean distance for child's throw 
const int THROW_LIMIT = 24;

// Constants for max height of a space 
const int MAX_PILE = 9;

// Constant for a snow pile too high to move through
const int OBSTACLE_HEIGHT = 6;

const int FORT_SIZE = 6;
