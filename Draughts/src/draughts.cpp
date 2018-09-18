#include "headers/draughts.h"

#include <vector>
#include <iostream>
#include <string>

void draughts::init(int (&board)[10][10]) 
{
	// for loop for inserting the pieces ... only black squares have pieces ... 
	// these are also arrays, meaning they start at 0 instead of 1, 
	// ... meaning the normal starting point of a draughts board (1) would have the absolute array posisition of [0, 1]
	// 2 would be [0, 3], 3 would be [0, 5], etc.

	// the loop starts at rank 10 (top of the board, ie where pos 1 is located) ...
	for (int i = 0; i < 10; i += 1) 
	{
		// When the loop reaches the middle (which has no pieces), it skips "i" to 6
		if (i == 4 || i == 5) 
		{
			for (int x = ((i + 1) % 2); x < 10; x += 2) {
				board[i][x] = 0;
				
				if ((x - 1) > -1)
					board[i][x-1] = -9;
			}
			continue;
		}


		// the loop then inserts a piece at every other position ... it starts at the inverse rank number (top is 0) 
		// .. then adds one and does a modulus operation to find the starting location ... ie it starts at 1 on the 1st rank (inverted rank), but at 0 on the 3rd rank (inversed rank).
		for (int x = ((i + 1) % 2); x < 10; x += 2) 
		{
			// white "men" are "1"'s and black "men" are "-1"'s
			board[i][x] = i > 5 ? 1 : -1;

			if ((x - 1) > -1)
				board[i][x-1] = -9;
		}
	}

	for (int i = 1; i < 10; i += 2) {
		board[i][9] = -9;
	}
}

void draughts::print(const int (&board)[10][10]) 
{
	for (int i = 0; i < 10; i++) 
	{
		for (int x = 0; x < 10; x++) 
		{
			std::string output = " [ ]";

			if (board[i][x] == -9) 
			{
				output[2] = '#';
			}
			else if (board[i][x] == 0) 
			{
				output[2] = '0';
			}
			else if (board[i][x] == 1)
			{
				output[2] = 'w';
			}
			else if (board[i][x] == 3)
			{
				output[2] = 'W';
			}
			else if (board[i][x] == -1)
			{
				output[2] = 'b';
			}
			else if (board[i][x] == -3)
			{
				output[2] = 'B';
			}
			else 
			{
				output[2] = '?';
			}

			std::cout << output;
		}
		std::cout << "\n \n";
	}
}

bool draughts::move(int(&board)[10][10], const int (&curPos)[2], const int(&desPos)[2])
{
	// if the position of the piece or the destination are invalid, return false.
	if (!((desPos[0] > -1) && (desPos[1] > -1) && (curPos[0] > -1) && (curPos[1] > -1)))
		return false;

	// if the target of movement is invalid (0 or -9), return false.
	else if (!board[curPos[0]][curPos[1]] || board[curPos[0]][curPos[1]] == -9)
		return false;

	// if the target of movement is a "man". execute this to attempt movement.
	else if (board[curPos[0]][curPos[1]] == 1 || board[curPos[0]][curPos[1]] == -1)
	{
		// first we check if the movement is ONE rank difference in the correct direction.
		// then we check if the movement is ONE file difference (pieces always change files whe moving)
		// then lastly we check if the spot the piece wants to move to is free(0)
		if (((-board[curPos[0]][curPos[1]] + curPos[0]) == desPos[0]) /**/ && /**/ ((curPos[1] + 1 == desPos[1]) || (curPos[1] - 1 == desPos[1])) /**/ && /**/ (!board[desPos[0]][desPos[1]]))
		{
			board[desPos[0]][desPos[1]] = board[curPos[0]][curPos[1]];
			board[curPos[0]][curPos[1]] = 0;
			return true;
		}

		// if all the conditions are not met, return false.
		else
			return false;
	}

	// if the target of movement is a king, execute this to atttemp movement.
	else if (board[curPos[0]][curPos[1]] == 3 || board[curPos[0]][curPos[1]] == -3)
	{
		// if the piece is moving downwards, execute this.
		if (curPos[0] < desPos[0])
		{
			// if the piece is moving diagonally right, execute this.
			if (desPos[0] - curPos[0] == desPos[1] - curPos[1])
			{
				int i = 0;
				while (desPos[0] != curPos[0] + i)
				{
					i++;
					if (board[curPos[0] + i][curPos[1] + i])
						return false;
				}
				board[desPos[0]][desPos[1]] = board[curPos[0]][curPos[1]];
				board[curPos[0]][curPos[1]] = 0;
				return true;
			}
			// if the piece is moving diagonally left, execute this.
			else if (desPos[0] - curPos[0] == curPos[1] - desPos[1])
			{
				int i = 0;
				while (desPos[0] != curPos[0] + i)
				{
					i++;
					if (board[curPos[0] + i][curPos[1] - i])
						return false;
				}
				board[desPos[0]][desPos[1]] = board[curPos[0]][curPos[1]];
				board[curPos[0]][curPos[1]] = 0;
				return true;
			}
			else
				return false;
		}
		// if the piece is moving upwards, execute this.
		else
		{
			// if the piece is moving diagonally right, execute this.
			if (curPos[0] - desPos[0] == desPos[1] - curPos[1])
			{
				int i = 0;
				while (desPos[0] != curPos[0] - i)
				{
					i++;
					if (board[curPos[0] - i][curPos[1] + i])
						return false;
				}
				board[desPos[0]][desPos[1]] = board[curPos[0]][curPos[1]];
				board[curPos[0]][curPos[1]] = 0;
				return true;
			}
			// if the piece is moving diagonally left, execute this.
			else if (curPos[0] - desPos[0] == curPos[1] - desPos[1])
			{
				int i = 0;
				while (desPos[0] != curPos[0] - i)
				{
					i++;
					if (board[curPos[0] - i][curPos[1] - i])
						return false;
				}
				board[desPos[0]][desPos[1]] = board[curPos[0]][curPos[1]];
				board[curPos[0]][curPos[1]] = 0;
				return true;
			}
			else
				return false;
		}
	}


	// If this return is reached, something went wrong. Return false.
	return false;
}

bool draughts::capture(int (&board)[10][10], const int(&capPos)[2], const int(&tarPos)[2], const int(&landPos)[2])
{
	// if the captuerer isn't a king, pass it to the normal capture funtion.
	if (!(board[capPos[0]][capPos[1]] == 3 || board[capPos[0]][capPos[1]] == -3))
		draughts::capture(board, capPos, tarPos);

	else
	{

	}

	return false;
}

bool draughts::capture(int(&board)[10][10], const int (&capPos)[2], const int (&tarPos)[2])
{
	if (!board[capPos[0]][capPos[1]] || board[capPos[0]][capPos[1]] == -9)
		return false;

	// execute this if the capturer is a "man"
	else if (board[capPos[0]][capPos[1]] == 1 || board[capPos[0]][capPos[1]] == -1)
	{
		// if the capture is going down and to the right
		if ((capPos[0] + 1 == tarPos[0]) && (capPos[1] + 1 == tarPos[1]))
		{
			// check if the pieces are on opposite teams
			if ((board[tarPos[0]][tarPos[1]] < 0 && 0 < board[capPos[0]][capPos[1]]) || (board[tarPos[0]][tarPos[1]] > 0 && 0 > board[capPos[0]][capPos[1]]))
			{
				// check if the "landing area" is clear
				if (!board[tarPos[0] + 1][tarPos[1] + 1])
				{
					// do the capture
					board[tarPos[0] + 1][tarPos[1] + 1] = board[capPos[0]][capPos[1]];
					board[capPos[0]][capPos[1]] = 0;
					board[tarPos[0]][tarPos[1]] = 0;
					return true;
				}
				else
					return false;
			}
			else
				return false;
		}
		// if the capture is going down and to the left
		else if ((capPos[0] + 1 == tarPos[0]) && (capPos[1] - 1 == tarPos[1]))
		{
			// check if the pieces are on opposite teams
			if ((board[tarPos[0]][tarPos[1]] < 0 && 0 < board[capPos[0]][capPos[1]]) || (board[tarPos[0]][tarPos[1]] > 0 && 0 > board[capPos[0]][capPos[1]]))
			{
				// check if the "landing area" is clear
				if (!board[tarPos[0] + 1][tarPos[1] - 1])
				{
					// do the capture
					board[tarPos[0] + 1][tarPos[1] - 1] = board[capPos[0]][capPos[1]];
					board[capPos[0]][capPos[1]] = 0;
					board[tarPos[0]][tarPos[1]] = 0;
					return true;
				}
				else
					return false;
			}
			else
				return false;
		}
		// if the capture is going up and to the right
		else if ((capPos[0] - 1 == tarPos[0]) && (capPos[1] + 1 == tarPos[1]))
		{
			// check if the pieces are on opposite teams
			if ((board[tarPos[0]][tarPos[1]] < 0 && 0 < board[capPos[0]][capPos[1]]) || (board[tarPos[0]][tarPos[1]] > 0 && 0 > board[capPos[0]][capPos[1]]))
			{
				// check if the "landing area" is clear
				if (!board[tarPos[0] - 1][tarPos[1] + 1])
				{
					// do the capture
					board[tarPos[0] - 1][tarPos[1] + 1] = board[capPos[0]][capPos[1]];
					board[capPos[0]][capPos[1]] = 0;
					board[tarPos[0]][tarPos[1]] = 0;
					return true;
				}
				else
					return false;
			}
			else
				return false;
		}
		// if the capture is going up and to the left
		else if ((capPos[0] - 1 == tarPos[0]) && (capPos[1] - 1 == tarPos[1]))
		{
			// check if the pieces are on opposite teams
			if ((board[tarPos[0]][tarPos[1]] < 0 && 0 < board[capPos[0]][capPos[1]]) || (board[tarPos[0]][tarPos[1]] > 0 && 0 > board[capPos[0]][capPos[1]]))
			{
				// check if the "landing area" is clear
				if (!board[tarPos[0] - 1][tarPos[1] - 1])
				{
					// do the capture
					board[tarPos[0] - 1][tarPos[1] - 1] = board[capPos[0]][capPos[1]];
					board[capPos[0]][capPos[1]] = 0;
					board[tarPos[0]][tarPos[1]] = 0;
					return true;
				}
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}

	// if the code reaches this point, something went wrong.
	return false;
}

std::vector<int[2][2]> draughts::GetPCap(int(&board)[10][10], const int(&pPos)[2])
{
	std::vector<int[2][2]> rvec(3);

	// check if the piece is a "man"	
	if (board[pPos[0]][pPos[1]] == 1 || board[pPos[0]][pPos[1]] == -1)
	{

	}
	return rvec;
}