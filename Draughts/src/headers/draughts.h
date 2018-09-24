#pragma once

#include <vector>
#include "blib.h"



namespace draughts 
{
	// the namespace "draughts" contains rules and manipulations of a game board ... 
	// an actual board (ie int ArrayNAME[10][10]) has to be present to be manipulated.

	class game
	{
		// TODO: IMPLEMENT
	};

	class moveSet
	{
	public:
		static enum moveType : unsigned char
		{
			MOVE,
			CAPTURE,
			INVALID
		};

		// variables
		moveType m_moveType;
		blib::pos m_startPos;
		std::vector<blib::pos> m_moves;
		std::vector<blib::pos> m_captured;


		// Constructors
		moveSet()
			: m_moveType(INVALID)
		{
			
		}

		moveSet(moveType moveT)
			: m_moveType(moveT)
		{

		}

		moveSet(moveType moveT, const int (&startPos)[2])
			:m_moveType(moveT) 
		{
			m_startPos[0] = startPos[0];
			m_startPos[1] = startPos[1];
		}

		moveSet(moveType moveT, const int &startPosX, const int &startPosY)
			:m_moveType(moveT), m_startPos(startPosX, startPosY)
		{

		}

		moveSet(moveType moveT, const blib::pos &startPos)
			:m_moveType(moveT), m_startPos(startPos)
		{

		}

		moveSet(const int &startPosX, const int &startPosY)
		{
			moveSet(MOVE, startPosX, startPosY);
		}

		moveSet(const blib::pos &startPos)
		{
			moveSet(MOVE, startPos);
		}
	};

	// Initializes the board put in byRef
	void init(int (&board)[10][10]);

	// Outputs the board state in text
	void print(const int(&board)[10][10]);

	// Moves a piece (takes movement rules into account, but does not check for captures.)
	bool move(int (&board)[10][10], const int (&curPos)[2], const int(&desPos)[2]);



	// TODO: REWRITE
	// Captures a piece (takes rules into account)
	bool capture(int(&board)[10][10], const int(&capturerPos)[2], const int (&targetPos)[2], const int(&LandingPos)[2]);

	bool capture(int(&board)[10][10], const int(&capturerPos)[2], const int (&targetPos)[2]);

	bool capture(int(&board)[10][10], const moveSet &moveset)
	{
		if (moveset.m_moveType == moveSet::CAPTURE)
		{

		}
	}
	
	// Gets all possible moves (cannot see captures)
	std::vector<moveSet> GetMoves(int(&board)[10][10]);

	// Gets all possible captures (finds best capture (rule)), returns { 0, 0 } if no captures exist.
	std::vector<moveSet> GetCaptures(int (&board)[10][10]);

	// Gets the captures of a specific piece
	std::vector<blib::pos> GetPCap(int(&board)[10][10], const int (&piecePos)[2]);

	// Gets moves/captures of a specific piece (calls GetCaptures to check if a move is legal at all), returns { 0, 0 } if no moves/captures are legal.
	std::vector<moveSet> GetPMovCap(int(&board)[10][10], const int &piecePos);
} 