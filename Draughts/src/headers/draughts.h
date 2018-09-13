#pragma once

#include <vector>

namespace draughts {
	// the namespace "draughts" contains rules and manipulations of a game board ... 
	// an actual board (ie int ArrayNAME[10][10]) has to be present to be manipulated.

	class game
	{
		// TODO: IMPLEMENT
	};

	// Initializes the board put in byRef
	void init(int (&board)[10][10]);

	// Outputs the board state in text
	void print(const int(&board)[10][10]);

	// Moves a piece (takes movement rules into account, but does not check for captures.)
	bool move(int (&board)[10][10], const int (&curPos)[2], const int(&desPos)[2]);

	// Captures a piece (takes rules into account)
	bool capture(int(&board)[10][10], const int(&capturerPos)[2], const int (&targetPos)[2], const int(&LandingPos)[2]);

	bool capture(int(&board)[10][10], const int(&capturerPos)[2], const int (&targetPos)[2]);
	
	// Gets all possible moves (cannot see captures)
	std::vector<int[2][2]> GetMoves(int(&board)[10][10]);

	// Gets all possible captures (finds best capture (rule)), returns { 0, 0 } if no captures exist.
	std::vector<int[2][2]> GetCaptures(int (&board)[10][10]);

	// Gets the captures of a specific piece
	std::vector<int[2][2]> GetPCap(int(&board)[10][10], const int &piecePos);

	// Gets moves/captures of a specific piece (calls GetCaptures to check if a move is legal at all), returns { 0, 0 } if no moves/captures are legal.
	std::vector<int[2][2]> GetPMovCap(int(&board)[10][10], const int &piecePos);
} 