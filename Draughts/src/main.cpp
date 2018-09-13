#include <iostream>

#include "headers/draughts.h"


int main() {
	int board[10][10];
	std::vector<int[2]> test(1);	

	draughts::init(board);
	draughts::print(board);

	board[6][3] = -1;
	board[5][2] = 1;

	std::cout << draughts::captureM(board, { 6, 3 }, { 5, 2 });
	std::cout << "--------------------------- \n \n";
	
	draughts::print(board);

	
	std::cout << test[0][0];

	std::cin.get();
}