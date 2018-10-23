#include "headers/blib.h"
#include "headers/draughts.h"

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>


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


bool draughts::move(int(&board)[10][10], const int(&curPos)[2], const int(&desPos)[2])
{
	draughts::moveDef moveD(draughts::moveDef::MOVE, curPos[0], curPos[1]);
	moveD.m_moves.push_back(blib::pos(curPos));

	return move(board, moveD);
}

bool draughts::move(int(&board)[10][10], const draughts::moveDef &move)
{
	// if the position of the piece or the destination are invalid, return false.
	if (!((move.m_moves[0].m_x > -1) && (move.m_moves[0].m_y > -1) && (move.m_staPos.m_x > -1) && (move.m_staPos.m_y > -1)))
		return false;

	// if the target of movement is invalid (0 or -9), return false.
	else if (!board[move.m_staPos.m_x][move.m_staPos.m_y] || board[move.m_staPos.m_x][move.m_staPos.m_y] == -9)
		return false;

	// if the target of movement is a "man". execute this to attempt movement.
	else if (board[move.m_staPos.m_x][move.m_staPos.m_y] == 1 || board[move.m_staPos.m_x][move.m_staPos.m_y] == -1)
	{
		// first we check if the movement is ONE rank difference in the correct direction.
		// then we check if the movement is ONE file difference (pieces always change files whe moving)
		// then lastly we check if the spot the piece wants to move to is free(0)
		if (((-board[move.m_staPos.m_x][move.m_staPos.m_y] + move.m_staPos.m_x) == move.m_moves[0].m_x) /**/ && /**/ ((move.m_staPos.m_y + 1 == move.m_moves[0].m_y) || (move.m_staPos.m_y - 1 == move.m_moves[0].m_y)) /**/ && /**/ (!board[move.m_moves[0].m_x][move.m_moves[0].m_y]))
		{
			board[move.m_moves[0].m_x][move.m_moves[0].m_y] = board[move.m_staPos.m_x][move.m_staPos.m_y];
			board[move.m_staPos.m_x][move.m_staPos.m_y] = 0;
			return true;
		}

		// if all the conditions are not met, return false.
		else
			return false;
	}

	// if the target of movement is a king, execute this to atttemp movement.
	else if (board[move.m_staPos.m_x][move.m_staPos.m_y] == 3 || board[move.m_staPos.m_x][move.m_staPos.m_y] == -3)
	{
		// if the piece is moving downwards, execute this.
		if (move.m_staPos.m_x < move.m_moves[0].m_x)
		{
			// if the piece is moving diagonally right, execute this.
			if (move.m_moves[0].m_x - move.m_staPos.m_x == move.m_moves[0].m_y - move.m_staPos.m_y)
			{
				int i = 0;
				while (move.m_moves[0].m_x != move.m_staPos.m_x + i)
				{
					i++;
					if (board[move.m_staPos.m_x + i][move.m_staPos.m_y + i])
						return false;
				}
				board[move.m_moves[0].m_x][move.m_moves[0].m_y] = board[move.m_staPos.m_x][move.m_staPos.m_y];
				board[move.m_staPos.m_x][move.m_staPos.m_y] = 0;
				return true;
			}
			// if the piece is moving diagonally left, execute this.
			else if (move.m_moves[0].m_x - move.m_staPos.m_x == move.m_staPos.m_y - move.m_moves[0].m_y)
			{
				int i = 0;
				while (move.m_moves[0].m_x != move.m_staPos.m_x + i)
				{
					i++;
					if (board[move.m_staPos.m_x + i][move.m_staPos.m_y - i])
						return false;
				}
				board[move.m_moves[0].m_x][move.m_moves[0].m_y] = board[move.m_staPos.m_x][move.m_staPos.m_y];
				board[move.m_staPos.m_x][move.m_staPos.m_y] = 0;
				return true;
			}
			else
				return false;
		}
		// if the piece is moving upwards, execute this.
		else
		{
			// if the piece is moving diagonally right, execute this.
			if (move.m_staPos.m_x - move.m_moves[0].m_x == move.m_moves[0].m_y - move.m_staPos.m_y)
			{
				int i = 0;
				while (move.m_moves[0].m_x != move.m_staPos.m_x - i)
				{
					i++;
					if (board[move.m_staPos.m_x - i][move.m_staPos.m_y + i])
						return false;
				}
				board[move.m_moves[0].m_x][move.m_moves[0].m_y] = board[move.m_staPos.m_x][move.m_staPos.m_y];
				board[move.m_staPos.m_x][move.m_staPos.m_y] = 0;
				return true;
			}
			// if the piece is moving diagonally left, execute this.
			else if (move.m_staPos.m_x - move.m_moves[0].m_x == move.m_staPos.m_y - move.m_moves[0].m_y)
			{
				int i = 0;
				while (move.m_moves[0].m_x != move.m_staPos.m_x - i)
				{
					i++;
					if (board[move.m_staPos.m_x - i][move.m_staPos.m_y - i])
						return false;
				}
				board[move.m_moves[0].m_x][move.m_moves[0].m_y] = board[move.m_staPos.m_x][move.m_staPos.m_y];
				board[move.m_staPos.m_x][move.m_staPos.m_y] = 0;
				return true;
			}
			else
				return false;
		}
	}


	// If this return is reached, something went wrong. Return false.
	return false;
}


blib::pos CapPos(const blib::pos &pPos, const int &CapNum, const int &CapLen)
{
	if (CapNum == 0)
	{
		return {pPos[0] - CapLen, pPos[1] - CapLen};
	}
	else if (CapNum == 1)
	{
		return { pPos[0] - CapLen, pPos[1] + CapLen };
	}
	else if (CapNum == 2)
	{
		return { pPos[0] + CapLen, pPos[1] + CapLen };
	}
	else if (CapNum == 3)
	{
		return { pPos[0] + CapLen, pPos[1] - CapLen };
	}
};


bool draughts::LegalCap(const int(&board)[10][10], const blib::pos &pPos, const int &CapNum)
{
	return draughts::LegalCap(board, pPos, CapNum, 0, board[pPos[0]][pPos[1]]);
}

bool draughts::LegalCap(const int(&board)[10][10], const blib::pos &pPos, const int &CapNum, const int &pType) {
	return draughts::LegalCap(board, pPos, CapNum, 0, pType);
}

bool draughts::LegalCap(const int(&board)[10][10], const blib::pos &pPos, const int &CapNum, const int &CapLeng, const int &pType)
{
	if (pType == 1 || pType == -1)
	{
		if (CapNum == 0)
		{
			return ((board[pPos[0] - 1][pPos[1] - 1] == -pType || board[pPos[0] - 1][pPos[1] - 1] == -3 * pType) && board[pPos[0] - 2][pPos[1] - 2] == 0);
		}
		else if (CapNum == 1)
		{
			return ((board[pPos[0] - 1][pPos[1] + 1] == -pType || board[pPos[0] - 1][pPos[1] + 1] == -3 * pType) && board[pPos[0] - 2][pPos[1] + 2] == 0);
		}
		else if (CapNum == 2)
		{
			return ((board[pPos[0] + 1][pPos[1] + 1] == -pType || board[pPos[0] + 1][pPos[1] + 1] == -3 * pType) && board[pPos[0] + 2][pPos[1] + 2] == 0);
		}
		else if (CapNum == 3)
		{
			return ((board[pPos[0] + 1][pPos[1] - 1] == -pType || board[pPos[0] + 1][pPos[1] - 1] == -3 * pType) && board[pPos[0] + 2][pPos[1] - 2] == 0);
		}
	}
	return false;
}

bool draughts::LegalCap(const int(&board)[10][10], const blib::pos &pPos, const int &CapNum, const int &CapLeng, const int &pType, blib::pos &CaptP)
{
	if (pType == 3 || pType == -3)
	{
		bool FoundCapPiece = false;
		bool FoundLandPos = false;

		if (CapNum == 0)
		{
			for (int i = 1; i < CapLeng + 1; i++)
			{
				if (board[pPos[0] - i][pPos[1] - i] == 0)
				{
					if (FoundCapPiece)
						FoundLandPos = true;
					continue;
				}
				else if (board[pPos[0] - i][pPos[1] - i] == -pType || board[pPos[0] - i][pPos[1] - i] == -(pType / 3))
				{
					if (FoundCapPiece)
						return false;
					else
					{
						FoundCapPiece = true;
						CaptP = { pPos[0] - i, pPos[1] - i };
					}
				}
				else if (board[pPos[0] - i][pPos[1] - i] == pType || board[pPos[0] - i][pPos[1] - i] == (pType / 3))
					return false;
			}
			
			return FoundCapPiece && FoundLandPos;
		}
		else if (CapNum == 1)
		{
			for (int i = 1; i < CapLeng + 1; i++)
			{
				if (board[pPos[0] - i][pPos[1] + i] == 0)
				{
					if (FoundCapPiece)
						FoundLandPos = true;
					continue;
				}
				else if (board[pPos[0] - i][pPos[1] + i] == -pType || board[pPos[0] - i][pPos[1] + i] == -(pType / 3))
				{
					if (FoundCapPiece)
						return false;
					else
					{
						FoundCapPiece = true;
						CaptP = { pPos[0] - i, pPos[1] + i };
					}
				}
				else if (board[pPos[0] - i][pPos[1] + i] == pType || board[pPos[0] - i][pPos[1] + i] == (pType / 3))
					return false;
			}

			return FoundCapPiece && FoundLandPos;
		}
		else if (CapNum == 2)
		{
			for (int i = 1; i < CapLeng + 1; i++)
			{
				if (board[pPos[0] + i][pPos[1] + i] == 0)
				{
					if (FoundCapPiece)
						FoundLandPos = true;
					continue;
				}
				else if (board[pPos[0] + i][pPos[1] + i] == -pType || board[pPos[0] + i][pPos[1] + i] == -(pType / 3))
				{
					if (FoundCapPiece)
						return false;
					else
					{
						FoundCapPiece = true;
						CaptP = { pPos[0] + i, pPos[1] + i };
					}
				}
				else if (board[pPos[0] + i][pPos[1] + i] == pType || board[pPos[0] + i][pPos[1] + i] == (pType / 3))
					return false;
			}

			return FoundCapPiece && FoundLandPos;
		}
		else if (CapNum == 3)
		{
			for (int i = 1; i < CapLeng + 1; i++)
			{
				if (board[pPos[0] + i][pPos[1] - i] == 0)
				{
					if (FoundCapPiece)
						FoundLandPos = true;
					continue;
				}
				else if (board[pPos[0] + i][pPos[1] - i] == -pType || board[pPos[0] + i][pPos[1] - i] == -(pType / 3))
				{
					if (FoundCapPiece)
						return false;
					else
					{
						FoundCapPiece = true;
						CaptP = { pPos[0] + i, pPos[1] - i };
					}
				}
				else if (board[pPos[0] + i][pPos[1] - i] == pType || board[pPos[0] + i][pPos[1] - i] == (pType / 3))
					return false;
			}

			return FoundCapPiece && FoundLandPos;
		}
	}
}


bool draughts::capture(int(&board)[10][10], moveDef &move)
{
	// if the capturing piece is invalid, terminate function.
	if (!board[move.m_staPos.m_x][move.m_staPos.m_y] || board[move.m_staPos.m_x][move.m_staPos.m_y] == -9)
		return false;

	// if the capturing piece is a "man", do this.
	if (board[move.m_staPos.m_x][move.m_staPos.m_y] == 1 || board[move.m_staPos.m_x][move.m_staPos.m_y] == -1)
	{
		if ((move.m_staPos + 2 >> 2) == move.m_moves[0])
		{

		}
		else if ((move.m_staPos + 2 << 2) == move.m_moves[0])
		{

		}
		else if ((move.m_staPos - 2 >> 2) == move.m_moves[0])
		{

		}
		else if ((move.m_staPos - 2 << 2) == move.m_moves[0])
		{

		}
	}
	// if the capturing piece is a king, do this.
	else if (board[move.m_staPos.m_x][move.m_staPos.m_y] == 3 || board[move.m_staPos.m_x][move.m_staPos.m_y] == -3)
	{

	}


	//// execute this if the capturer is a "man"
	//else if (board[move.m_staPos.m_x][move.m_staPos.m_y] == 1 || board[move.m_staPos.m_x][move.m_staPos.m_y] == -1)
	//{
	//	// if the capture is going down and to the right
	//	if ((move.m_staPos.m_x + 1 == tarPos[0]) && (move.m_staPos.m_y + 1 == tarPos[1]))
	//	{
	//		// check if the pieces are on opposite teams
	//		if ((board[tarPos[0]][tarPos[1]] < 0 && 0 < board[move.m_staPos.m_x][move.m_staPos.m_y]) || (board[tarPos[0]][tarPos[1]] > 0 && 0 > board[move.m_staPos.m_x][move.m_staPos.m_y]))
	//		{
	//			// check if the "landing area" is clear
	//			if (!board[tarPos[0] + 1][tarPos[1] + 1])
	//			{
	//				// do the capture
	//				board[tarPos[0] + 1][tarPos[1] + 1] = board[move.m_staPos.m_x][move.m_staPos.m_y];
	//				board[move.m_staPos.m_x][move.m_staPos.m_y] = 0;
	//				board[tarPos[0]][tarPos[1]] = 0;
	//				return true;
	//			}
	//			else
	//				return false;
	//		}
	//		else
	//			return false;
	//	}
	//	// if the capture is going down and to the left
	//	else if ((move.m_staPos.m_x + 1 == tarPos[0]) && (move.m_staPos.m_y - 1 == tarPos[1]))
	//	{
	//		// check if the pieces are on opposite teams
	//		if ((board[tarPos[0]][tarPos[1]] < 0 && 0 < board[move.m_staPos.m_x][move.m_staPos.m_y]) || (board[tarPos[0]][tarPos[1]] > 0 && 0 > board[move.m_staPos.m_x][move.m_staPos.m_y]))
	//		{
	//			// check if the "landing area" is clear
	//			if (!board[tarPos[0] + 1][tarPos[1] - 1])
	//			{
	//				// do the capture
	//				board[tarPos[0] + 1][tarPos[1] - 1] = board[move.m_staPos.m_x][move.m_staPos.m_y];
	//				board[move.m_staPos.m_x][move.m_staPos.m_y] = 0;
	//				board[tarPos[0]][tarPos[1]] = 0;
	//				return true;
	//			}
	//			else
	//				return false;
	//		}
	//		else
	//			return false;
	//	}
	//	// if the capture is going up and to the right
	//	else if ((move.m_staPos.m_x - 1 == tarPos[0]) && (move.m_staPos.m_y + 1 == tarPos[1]))
	//	{
	//		// check if the pieces are on opposite teams
	//		if ((board[tarPos[0]][tarPos[1]] < 0 && 0 < board[move.m_staPos.m_x][move.m_staPos.m_y]) || (board[tarPos[0]][tarPos[1]] > 0 && 0 > board[move.m_staPos.m_x][move.m_staPos.m_y]))
	//		{
	//			// check if the "landing area" is clear
	//			if (!board[tarPos[0] - 1][tarPos[1] + 1])
	//			{
	//				// do the capture
	//				board[tarPos[0] - 1][tarPos[1] + 1] = board[move.m_staPos.m_x][move.m_staPos.m_y];
	//				board[move.m_staPos.m_x][move.m_staPos.m_y] = 0;
	//				board[tarPos[0]][tarPos[1]] = 0;
	//				return true;
	//			}
	//			else
	//				return false;
	//		}
	//		else
	//			return false;
	//	}
	//	// if the capture is going up and to the left
	//	else if ((move.m_staPos.m_x - 1 == tarPos[0]) && (move.m_staPos.m_y - 1 == tarPos[1]))
	//	{
	//		// check if the pieces are on opposite teams
	//		if ((board[tarPos[0]][tarPos[1]] < 0 && 0 < board[move.m_staPos.m_x][move.m_staPos.m_y]) || (board[tarPos[0]][tarPos[1]] > 0 && 0 > board[move.m_staPos.m_x][move.m_staPos.m_y]))
	//		{
	//			// check if the "landing area" is clear
	//			if (!board[tarPos[0] - 1][tarPos[1] - 1])
	//			{
	//				// do the capture
	//				board[tarPos[0] - 1][tarPos[1] - 1] = board[move.m_staPos.m_x][move.m_staPos.m_y];
	//				board[move.m_staPos.m_x][move.m_staPos.m_y] = 0;
	//				board[tarPos[0]][tarPos[1]] = 0;
	//				return true;
	//			}
	//			else
	//				return false;
	//		}
	//		else
	//			return false;
	//	}
	//	else
	//		return false;
	//}

	// if the code reaches this point, something went wrong.
	return false;
}

//std::vector<draughts::moveDef> GetCaptures(int(&board)[10][10])
//{
//
//}

std::vector<draughts::moveDef> draughts::GetPCap(int(&board)[10][10], const blib::pos &pPos)
{
	std::vector<draughts::moveDef> rvec(4);

	// check if the piece is a "man"	
	if (board[pPos.m_x][pPos.m_y] == 1 || board[pPos.m_x][pPos.m_y] == -1)
	{
		for(int i = 0; i < 4; i++) 
		{
			if (draughts::LegalCap(board, pPos, i))
			{
				draughts::moveDef temp(draughts::moveDef::CAPTURE, pPos, CapPos(pPos, i, 2), CapPos(pPos, i, 1));

				rvec.push_back(temp);

				draughts::GetPCap(
					board, 
					((i < 2) ? (i + 2) : (i - 2)), 
					board[pPos[0]][pPos[1]], 
					rvec, 
					((rvec.size()) - 1), 
					CapPos(pPos, i, 2)
				);
			}
		}
	}
	else if (board[pPos.m_x][pPos.m_y] == 3 || board[pPos.m_x][pPos.m_y] == -3)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int x = 0; x < 10; x++)
			{
				if (i == 0)
				{
					if ((pPos[0] - x < 0) || (pPos[1] - x < 0))
						break;
				}
				else if (i == 1)
				{
					if ((pPos[0] - x < 0) || (pPos[1] + x > 9))
						break;
				}
				else if (i == 2)
				{
					if ((pPos[0] + x > 9) || (pPos[1] + x > 9))
						break;
				}
				else if (i == 3)
				{
					if ((pPos[0] + x > 9) || (pPos[1] - x < 0))
						break;
				}
				blib::pos CPOS;
				if (draughts::LegalCap(board, pPos, i, x, board[pPos[0]][pPos[1]], CPOS))
				{
					draughts::moveDef temp(draughts::moveDef::CAPTURE, pPos, CapPos(pPos, i, x), CPOS);

					rvec.push_back(temp);

					draughts::GetPCap(
						board,
						((i < 2) ? (i + 2) : (i - 2)),
						board[pPos[0]][pPos[1]],
						rvec,
						((rvec.size()) - 1),
						CapPos(pPos, i, x)
					);
				}
			}
		}
	}

	std::sort(rvec.begin(), rvec.end(), [](draughts::moveDef a, draughts::moveDef b) {
		return a.m_moves.size() > b.m_moves.size();
	});

	int largestFound = rvec[0].m_moves.size();
	//std::cout << largestFound << "\n";
	int delBegin = 0;

	for (int i = 0; i < rvec.size(); i++)
	{
		//std::cout << rvec[i].m_moves.size() << " ; " << (rvec[i].m_moves.size() < largestFound) << "\n";
		if (rvec[i].m_moves.size() < largestFound)
		{
			delBegin = i;
			break;
		}
	}
	rvec.erase((rvec.begin() + delBegin), rvec.end());

	return rvec;
}

std::vector<draughts::moveDef> draughts::GetPCap(int(&board)[10][10], const int &from, const int &pType, std::vector<draughts::moveDef> &CapList, const int &stamovnum, const blib::pos &newPos)
{
	
	if (pType == 1 || pType == -1)
	{
		for (int i = 0; i < 4; i++)
		{
			if (i != from)
			{
				if (draughts::LegalCap(board, newPos, i, pType))
				{
					if(CapList[stamovnum].m_capt.size() > 3) 
					{
						bool checker = true;
						for (int x = 0; x < CapList[stamovnum].m_capt.size(); x++)
						{
							if (CapList[stamovnum].m_capt[x] == CapPos(newPos, i, 1))
							{
								checker = false;
								break;
							}
								
						}
						if (!checker)
							continue;
					}
					
					draughts::moveDef temp = CapList[stamovnum];

					temp.m_moves.push_back(CapPos(newPos, i, 2));
					temp.m_capt.push_back(CapPos(newPos, i, 1));

					CapList.push_back(temp);

					draughts::GetPCap(
						board,
						(i < 2) ? (i + 2) : (i - 2),
						pType,
						CapList,
						CapList.size() - 1,
						CapPos(newPos, i, 2)
					);
					
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (i != from)
			{
				for (int x = 0; x < 10; x++)
				{
					if (i == 0)
					{
						if ((newPos[0] - x < 0) || (newPos[1] - x < 0))
							break;
					}
					else if (i == 1)
					{
						if ((newPos[0] - x < 0) || (newPos[1] + x > 9))
							break;
					}
					else if (i == 2)
					{
						if ((newPos[0] + x > 9) || (newPos[1] + x > 9))
							break;
					}
					else if (i == 3)
					{
						if ((newPos[0] + x > 9) || (newPos[1] - x < 0))
							break;
					}
					blib::pos CPOS;
					if (draughts::LegalCap(board, newPos, i, x, pType, CPOS))
					{
						if (CapList[stamovnum].m_capt.size() > 3)
						{
							bool checker = true;
							for (int x = 0; x < CapList[stamovnum].m_capt.size(); x++)
							{
								if (CapList[stamovnum].m_capt[x] == CPOS)
								{
									checker = false;
									break;
								}

							}
							if (!checker)
								continue;
						}

						draughts::moveDef temp = CapList[stamovnum];

						temp.m_moves.push_back(CapPos(newPos, i, x));
						temp.m_capt.push_back(CPOS);

						CapList.push_back(temp);

						draughts::GetPCap(
							board,
							(i < 2) ? (i + 2) : (i - 2),
							pType,
							CapList,
							CapList.size() - 1,
							CapPos(newPos, i, x)
						);
					}
				}
			}
		}
	}

	return CapList;
}