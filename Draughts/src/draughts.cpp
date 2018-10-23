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

bool draughts::move(int(&board)[10][10], draughts::moveDef &move)
{
	if (!board[move.m_staPos.m_x][move.m_staPos.m_y] || board[move.m_staPos.m_x][move.m_staPos.m_y] == -9)
		return false;

	std::vector<draughts::moveDef> moveList = GetPCap(board, move.m_staPos);

	for (int i = 0; i < moveList.size(); i++)
	{
		if (move == moveList[i])
		{
			draughts::ComMov(board, move);
			return true;
		}
	}

	// if the code reaches this point, something went wrong.
	return false;
}


void draughts::ComMov(int(&board)[10][10], const moveDef &move)
{
	board[move.m_moves[move.m_moves.size() - 1][0]][move.m_moves[move.m_moves.size() - 1][1]] = board[move.m_staPos[0]][move.m_staPos[1]];

	board[move.m_staPos[0]][move.m_staPos[1]] = 0;
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


bool draughts::LegalKMov(const int(&board)[10][10], const blib::pos &pPos, const int &CapNum, const int &CapLeng)
{
	if (CapNum == 0)
	{
		for (int i = 1; i < CapLeng + 1; i++)
		{
			if (pPos[0] - i < 0 || pPos[1] - i < 0)
				return false;

			if (board[pPos[0] - i][pPos[1] - i])
			{
				return false;
			}
		}
		return true;
	}
	else if (CapNum == 1)
	{
		for (int i = 1; i < CapLeng + 1; i++)
		{
			if (pPos[0] - i < 0 || pPos[1] + i < 0)
				return false;

			if (board[pPos[0] - i][pPos[1] + i])
			{
				return false;
			}
		}
		return true;
	}
	else if (CapNum == 2)
	{
		for (int i = 1; i < CapLeng + 1; i++)
		{
			if (pPos[0] + i < 0 || pPos[1] + i < 0)
				return false;

			if (board[pPos[0] + i][pPos[1] + i])
			{
				return false;
			}
		}
		return true;
	}
	else if (CapNum == 3)
	{
		for (int i = 1; i < CapLeng + 1; i++)
		{
			if (pPos[0] + i < 0 || pPos[1] - i < 0)
				return false;

			if (board[pPos[0] + i][pPos[1] - i])
			{
				return false;
			}
		}
		return true;
	}
}




bool draughts::capture(int(&board)[10][10], moveDef &move)
{
	// if the capturing piece is invalid, terminate function.
	if (!board[move.m_staPos.m_x][move.m_staPos.m_y] || board[move.m_staPos.m_x][move.m_staPos.m_y] == -9)
		return false;

	std::vector<draughts::moveDef> moveList = GetPCap(board, move.m_staPos);

	for (int i = 0; i < moveList.size(); i++)
	{
		if (move == moveList[i])
		{
			draughts::ComCapture(board, move);
			return true;
		}
	}

	// if the code reaches this point, something went wrong.
	return false;
}

void draughts::ComCapture(int(&board)[10][10], const moveDef &move)
{
	board[move.m_moves[move.m_moves.size()-1][0]][move.m_moves[move.m_moves.size() - 1][1]] = board[move.m_staPos[0]][move.m_staPos[1]];

	for (int i = 0; i < move.m_capt.size(); i++)
	{
		board[move.m_capt[i][0]][move.m_capt[i][1]] = 0;
	}

	board[move.m_staPos[0]][move.m_staPos[1]] = 0;
}



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


std::vector<draughts::moveDef> draughts::GetPMovCap(int(&board)[10][10], const blib::pos &pPos)
{
	std::vector<draughts::moveDef> MoveList = draughts::GetPCap(board, pPos);

	if (!(MoveList.size()))
	{
		int pType = board[pPos[0]][pPos[1]];
		if (pType == 1 || pType == -1)
		{

			if (board[pPos[0] - pType][pPos[1 - (pPos[1] > 0 ? 1 : 0)]] == 0)
			{
				MoveList.push_back(draughts::moveDef(draughts::moveDef::MOVE, pPos, {pPos[0] - pType, pPos[1] - 1}));
			}
			if (board[pPos[0] - pType][pPos[1 + (pPos[1] < 9 ? 1 : 0)]] == 0)
			{
				MoveList.push_back(draughts::moveDef(draughts::moveDef::MOVE, pPos, { pPos[0] - pType, pPos[1] + 1 }));
			}
		}
		else if (pType == 3 || pType == -3)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int x = 1; x < 10; x++)
				{
					if (LegalKMov(board, pPos, i, x))
					{
						if (i == 0)
							MoveList.push_back(draughts::moveDef(draughts::moveDef::MOVE, pPos, { pPos[0] - x, pPos[1] - x }));
						else if (i == 1)
							MoveList.push_back(draughts::moveDef(draughts::moveDef::MOVE, pPos, { pPos[0] - x, pPos[1] + x }));
						else if (i == 2)
							MoveList.push_back(draughts::moveDef(draughts::moveDef::MOVE, pPos, { pPos[0] + x, pPos[1] + x }));
						else if (i == 3)
							MoveList.push_back(draughts::moveDef(draughts::moveDef::MOVE, pPos, { pPos[0] + x, pPos[1] - x }));
					}
				}
			}
		}
		else
		{
			return MoveList;
		}
	}

	return MoveList;
}


std::vector<draughts::moveDef> draughts::GetLegalMoves(int(&board)[10][10])
{
	std::vector<draughts::moveDef> retvec(30);

	for (int i = 0; i < 10; i += 1)
	{
		for (int x = ((i + 1) % 2); x < 10; x += 2)
		{
			//std::cout << board[i][x] << "\n";
			std::vector<draughts::moveDef> temp = GetPMovCap(board, { i, x });
			retvec.insert(retvec.end(), temp.begin(), temp.end());
		}
	}

	int largestFound = retvec[0].m_moves.size();
	//std::cout << largestFound << "\n";
	int delBegin = 0;

	for (int i = 0; i < retvec.size(); i++)
	{
		//std::cout << rvec[i].m_moves.size() << " ; " << (rvec[i].m_moves.size() < largestFound) << "\n";
		if (retvec[i].m_moves.size() < largestFound)
		{
			delBegin = i;
			break;
		}
	}
	retvec.erase((retvec.begin() + delBegin), retvec.end());
	
	return retvec;
}

std::vector<draughts::moveDef> draughts::GetLegalMoves(int(&board)[10][10], const int side)
{
	std::vector<draughts::moveDef> retvec(30);

	for (int i = 0; i < 10; i += 1)
	{
		for (int x = ((i + 1) % 2); x < 10; x += 2)
		{
			//std::cout << board[i][x] << "\n";
			if (board[i][x] == side || board[i][x] == side * 3)
			{
				std::vector<draughts::moveDef> temp = GetPMovCap(board, { i, x });
				retvec.insert(retvec.end(), temp.begin(), temp.end());
			}
		}
	}

	return retvec;
}