#include <string>
#include <iostream>
#include <array>
#include <time.h>


#include "headers/draughts.h"
#include "headers/blib.h"

bool term = true;
bool* terminator = &term;

void wait(int seconds)
{
	clock_t endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endwait) {}
}


int main() {
	int board[10][10];

	draughts::init(board);
	draughts::print(board);



	std::cout << "--------------------------- \n \n";

	board[4][1] = 1;
	board[2][3] = 0;

	draughts::print(board);

	std::vector<draughts::moveDef> testVector = draughts::GetPCap(board, { 4,1 });


	for (int i = 0; i < (int)(testVector.size()); i++) {
		for (int x = 0; x < (int)(testVector[i].m_moves.size()); x++) {
			std::cout << " " << testVector[i].m_moves[x][0] << " - " << testVector[i].m_moves[x][1] << " ";
			std::cout << ";";
		}
		std::cout << std::endl;
	}

	system("pause");
}