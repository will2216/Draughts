#include <string>
#include <iostream>
#include <array>
#include <time.h>


#include "headers/draughts.h"
#include "headers/blib.h"


void wait(int seconds)
{
	clock_t endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endwait) {}
}


int main() {

	draughts::game newGame;

	newGame.start();

	system("pause");
}



