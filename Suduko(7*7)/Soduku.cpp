// Logic

// 9*9 logic is : 
// 1. Same number must not exist in same row
// 2. Same number must not exist in same column
// 3. Same number must not exist in 9*9 box

// Just replace logic 3 with :
// Same number must not exist in the same color
// For that created struct which consists value and color of each cell of 7*7 grid 

#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

using std::cout;
using std::endl;
using std::cin;

#define DIM 7
#define BLANK 0
#define SPACE " "
#define LINE "|"
#define NEW_ROW "-------------------------------------"
#define GRID_FULL std::make_pair(9, 9)

struct soduku_field
{
	int value;
	char color;
	
};

void print_grid(soduku_field grid[DIM][DIM])
{
	for (int i = 0; i < DIM; i++)
	{
		cout << SPACE << SPACE << SPACE << SPACE << endl;
		cout << NEW_ROW << endl;
		for (int j = 0; j < DIM; j++)
		{
			cout << SPACE;
			if (BLANK == grid[i][j].value)
			{
				cout << SPACE;
			}
			else
			{
				cout << grid[i][j].value;
			}
			cout << SPACE;
			cout << LINE;
		}
	}
	cout << endl << NEW_ROW << endl << endl;
}
bool used_in_row(soduku_field grid[DIM][DIM], int row, int num)
{
	for (int col = 0; col < DIM; col++)
		if (grid[row][col].value == num)
		{
			return true;
		}
	return false;
}

// Returns a boolean which indicates whether any assigned entry
// in the specified column matches the given number. 
bool used_in_col(soduku_field grid[DIM][DIM], int col, int num)
{
	for (int row = 0; row < DIM; row++)
		if (grid[row][col].value == num)
		{
			return true;
		}
	return false;
}

// Returns a boolean which indicates whether any assigned entry
// within the specified 3x3 box matches the given number. 
bool used_in_color(soduku_field grid[DIM][DIM], int num, char color)
{
	for (int row = 0; row < DIM; row++)
		for (int col = 0; col < DIM; col++)
			if (grid[row][col].value == num && grid[row][col].color == color) 
			{
				return true;
			}
	return false;
}

// Returns a boolean which indicates whether it will be legal to assign
// num to the given row,col location.
bool is_safe(soduku_field grid[DIM][DIM], int row, int col, int num)
{
	// Check if 'num' is not already placed in current row,
	// current column and current 3x3 box 
	return !used_in_row(grid, row, num) &&
		!used_in_col(grid, col, num) &&
		!used_in_color(grid, num, grid[row][col].color);
}

// Searches the grid to find an entry that is still unassigned. If
// found, the reference parameters row, col will be set the location
// that is unassigned, and true is returned. If no unassigned entries
// remain, false is returned. 
std::pair<int, int> get_unassigned_location(soduku_field grid[DIM][DIM])
{
	for (int row = 0; row < DIM; row++)
		for (int col = 0; col < DIM; col++)
			if (grid[row][col].value == BLANK)
			{
				return std::make_pair(row, col);
			}
	return GRID_FULL;
}

// Takes a partially filled-in grid and attempts to assign values to
// all unassigned locations in such a way to meet the requirements
// for Sudoku solution (non-duplication across rows, columns, and boxes) 
bool solve_soduko(soduku_field grid[DIM][DIM])
{
	// If the Soduko grid has been filled, we are done
	if (GRID_FULL == get_unassigned_location(grid))
	{
		return true; 
	}

	// Get an unassigned Soduko grid location
	std::pair<int, int> row_and_col = get_unassigned_location(grid);
	int row = row_and_col.first;
	int col = row_and_col.second;

	// Consider digits 1 to 9
	for (int num = 1; num <= DIM; num++)
	{
		// If placing the current number in the current
		// unassigned location is valid, go ahead
		if (is_safe(grid, row, col, num))
		{
			// Make tentative assignment
			grid[row][col].value = num;

			// Do the same thing again recursively. If we go 
			// through all of the recursions, and in the end 
			// return true, then all of our number placements 
			// on the Soduko grid are valid and we have fully
			// solved it
			if (solve_soduko(grid))
			{
				return true;
			}

			// As we were not able to validly go through all 
			// of the recursions, we must have an invalid number
			// placement somewhere. Lets go back and try a 
			// different number for this particular unassigned location
			grid[row][col].value = BLANK;
		}
	}

	// If we have gone through all possible numbers for the current unassigned
	// location, then we probably assigned a bad number early. Lets backtrack 
	// and try a different number for the previous unassigned locations.
	return false; 
}


int main()
{
	soduku_field grid[DIM][DIM];
		
	for(int i=0;i<DIM;i++)
	    for(int j=0;j<DIM;j++)
	        cin>>grid[i][j].value;
	for(int i=0;i<DIM;i++)
	    for(int j=0;j<DIM;j++)
	        cin>>grid[i][j].color;
	print_grid(grid);

	if (true == solve_soduko(grid))
	{
		print_grid(grid);
	}
	else
	{
		cout << "No solution exists for the given Soduko" << endl << endl;
	}
	return 0;
}


