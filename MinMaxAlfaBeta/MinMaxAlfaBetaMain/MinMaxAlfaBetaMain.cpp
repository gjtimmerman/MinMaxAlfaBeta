// MinMaxAlfaBetaMain.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "../MinMaxAlfaBeta/framework.h"

int main()
{
	PlayingTable table("AbCNOBapcnoP");
	table.notrump = true;
	table.trump = Suit::Hearts;
	table.declarer = (int)Compass::East;
	Trick t;
	PlayingTable bestMoves = playAllTricksMinMax(table, -1, t);
	std::cout << bestMoves.tricksWonByDeclaringSide << std::endl;
	std::cout << "All tricks:\n";
	for (int i = 0; i < NUMBER_OF_CARDS; i++)
	{
		std::cout << "Trick " << i << std::endl;
		std::cout << "Lead " << bestMoves.tricks[i].lead << std::endl;
		for (int j = 0; j < NUMBER_OF_PLAYERS; j++)
			std::cout << "Player " << j << " , Card: (" << (int)bestMoves.tricks[i].trick[j].suit << "," << (int)bestMoves.tricks[i].trick[j].value << ")\n";
	}

}
