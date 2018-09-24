#include <iostream>
#include <array>

#include "headers/draughts.h"
#include "headers/blib.h"




int main() {
	int board[10][10];

	draughts::init(board);
	draughts::print(board);

	std::array<int, 2> hello = { 0,2 };

	board[6][3] = -1;
	board[5][2] = 1;

	std::cout << draughts::capture(board, { 6, 3 }, { 5, 2 });
	std::cout << "--------------------------- \n \n";
	
	draughts::print(board);



	draughts::moveSet moveset(draughts::moveSet::MOVE, { 1,0 });


	moveset.m_moves.push_back(blib::pos{ 0,1 });


	std::cout << moveset.m_moves[0][0];

	std::cin.get();
}