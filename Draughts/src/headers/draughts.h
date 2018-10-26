#pragma once

#include <vector>
#include "blib.h"

 

namespace draughts
{
	// the namespace "draughts" contains rules and manipulations of a game board ... 
	// an actual board (ie int ArrayNAME[10][10]) has to be present to be manipulated.

	struct moveDef
	{
		enum moveType : unsigned char
		{
			MOVE,
			CAPTURE,
			INVALID
		};

		// variables
		moveType m_moveType;
		blib::pos m_staPos;
		std::vector<blib::pos> m_moves;
		// you don't have to specify which pieces are captured if you're using the capture function.
		std::vector<blib::pos> m_capt;


		// Constructors
		moveDef()
			: m_moveType(INVALID)
		{

		}

		moveDef(moveType moveT)
			: m_moveType(moveT)
		{

		}

		moveDef(moveType moveT, const int(&startPos)[2])
			:m_moveType(moveT)
		{
			m_staPos[0] = startPos[0];
			m_staPos[1] = startPos[1];
		}

		moveDef(moveType moveT, const int &startPosX, const int &startPosY)
			:m_moveType(moveT), m_staPos(startPosX, startPosY)
		{

		}

		moveDef(moveType moveT, const blib::pos &startPos)
			:m_moveType(moveT), m_staPos(startPos)
		{

		}

		moveDef(moveType moveT, const blib::pos &startPos, const blib::pos &move)
			:m_moveType(moveT), m_staPos(startPos)
		{
			m_moves.push_back(move);
		}

		moveDef(moveType CAPTURE, const blib::pos &startPos, const blib::pos &move, const blib::pos &capturedP)
			:m_moveType(CAPTURE), m_staPos(startPos)
		{
			m_moves.push_back(move);
			m_capt.push_back(capturedP);
		}

		moveDef(const int &startPosX, const int &startPosY)
		{
			moveDef(MOVE, startPosX, startPosY);
		}

		moveDef(const blib::pos &startPos)
		{
			moveDef(MOVE, startPos);
		}


		// Operator overloading
		bool operator==(const moveDef &input)
		{
			if (m_moveType != input.m_moveType)
				return false;

			if (m_staPos != input.m_staPos)
				return false;

			if (m_moves.size() == input.m_moves.size())
			{
				for (int i = 0; i < input.m_moves.size(); i++)
				{
					if (!(m_moves[i] == input.m_moves[i]))
						return false;
				}
			}

			if (m_moveType == CAPTURE)
			{
				if (m_capt.size() == input.m_capt.size())
				{
					for (int i = 0; i < input.m_capt.size(); i++)
					{
						if (!(m_capt[i] == input.m_capt[i]))
							return false;
					}
				}
			}

			return true;
		}
	};

	// Initializes the board put in byRef
	void init(int(&board)[10][10]);

	// Outputs the board state in text
	void print(const int(&board)[10][10]);

	// Moves a piece (takes movement rules into account, but does not check for captures.)
	bool move(int(&board)[10][10], moveDef &move);

	bool move(int(&board)[10][10], const int(&curPos)[2], const int(&desPos)[2]);


	// TODO: REWRITE
	// Captures a piece/pieces (takes rules into account, does not check for additional captures (use getPCap, to get complete capture move))

	//bool capture(int(&board)[10][10], const int(&capturerPos)[2], const int (&targetPos)[2], const int(&LandingPos)[2]);

	bool capture(int(&board)[10][10], moveDef &move);



	void ComCapture(int(&board)[10][10], const moveDef &move, int &pNum);


	void ComMov(int(&board)[10][10], const moveDef &move);


	// Gets all possible moves (sees captures)
	std::vector<moveDef> GetLegalMoves(int(&board)[10][10]);

	std::vector<moveDef> GetLegalMoves(int(&board)[10][10], const int side);

	// Checks if a capture is legal (captures start in the top left and go clockwise, they also start at 0).
	bool LegalCap(const int(&board)[10][10], const blib::pos &pPos, const int &CapNum, const int &CapLeng, const int &pType, blib::pos &CaptP);

	bool LegalCap(const int(&board)[10][10], const blib::pos &pPos, const int &CapNum, const int &CapLeng, const int &pType);

	bool LegalCap(const int(&board)[10][10], const blib::pos &pPos, const int &CapNum, const int &pType);

	bool LegalCap(const int(&board)[10][10], const blib::pos &pPos, const int &CapNum);

	// Checks if a King move is legal
	bool LegalKMov(const int(&board)[10][10], const blib::pos &pPos, const int &CapNum, const int &CapLeng);


	// Gets the captures of a specific piece
	std::vector<moveDef> GetPCap(int(&board)[10][10], const blib::pos &piecePos);

	std::vector<moveDef> GetPCap(int(&board)[10][10], const int &from, const int &pType, std::vector<draughts::moveDef> &CapList, const int &smovnum, const blib::pos &newPos);

	// Gets moves/captures of a specific piece (does not call GetCaptures to check if a move is legal at all), returns an empty list if no moves/captures are legal.
	std::vector<moveDef> GetPMovCap(int(&board)[10][10], const blib::pos &pPos);


	// Finds a move using PDN plie
	moveDef FindMove(const std::string &input);


	// Turns a number into a blib::pos
	blib::pos posFNum(const int &input);

	
	// check if two moves start and end the same (also have to be the same move type)
	bool eqMove(draughts::moveDef &mov1, draughts::moveDef &mov2);


	// A game class
	class game
	{
		int m_board[10][10];

		int m_turn = 1;
		int m_numPieces = 40;
		int kingMoves = 0;

		bool m_multiplayer;


		// Constructors
	public:
		game()
		{
			init(m_board);
		}

		game(int(&board)[10][10])
		{
			for (int i = 0; i < 10; i++)
			{
				for (int x = 0; x < 10; x++)
				{
					m_board[i][x] = board[i][x];
				}
			}
		}


		// functions

		//starts the game
		void start();




	private:

	};
} 