// MinMaxAlfaBetaMain.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "../MinMaxAlfaBeta/framework.h"

int main()
{
	PlayingTable table("AbCdENOBaQPDcqrnopeR");
	table.notrump = false;
	table.trump = Suit::Clubs;
	table.declarer = (int)Compass::North;
	Trick t;
	time_t starttime = time(NULL);
	PlayingTable bestMoves = playAllTricksMinMax(table, -1, t);
	std::cout << bestMoves.tricksWonByDeclaringSide << std::endl;
	std::cout << "All tricks:\n";
	for (int i = 0; i < NUMBER_OF_CARDS; i++)
	{
		std::cout << "Trick " << i << std::endl;
		std::cout << "Lead " << bestMoves.tricks[i].lead << std::endl;
		for (int j = 0; j < NUMBER_OF_PLAYERS; j++)
			std::cout << "Player " << j << " , Card: (" << bestMoves.tricks[i].trick[j] << ")\n";
	}
	std::cout << "ClockTicks: " << time(NULL) - starttime << std::endl;
}
