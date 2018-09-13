#include <iostream>

#include "headers/draughts.h"


int main() {
	int board[10][10];
	std::vector<int[2]> test(1);	

	draughts::init(board);
	draughts::print(board);


	std::cout << draughts::move(board, { 5, 3 }, { 4, 4 });
	std::cout << "--------------------------- \n \n";
	
	draughts::print(board);

	
	std::cout << test[0][0];

	std::cin.get();
}