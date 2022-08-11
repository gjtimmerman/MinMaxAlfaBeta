// MinMaxAlfaBetaMain.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>

#include "../MinMaxAlfaBeta/framework.h"

extern PlayingTable tables[NUMBER_OF_CARDS];

int main()
{
//	PlayingTable table("AbCdEsTiUwkmYNOBaQFShujKlyPDcqrfGIHxWLMnopeRtgvVJXZz");
//	PlayingTable table("AbCdEsTiUwkmYNOBaQFShujKlyPDcqrfGIHxWLMnopeR");
//	PlayingTable table("AbCdEsTiUwkmYNOBaQFShujKlyPDcqrfGIHxWLMn");
//	PlayingTable table("AbCdEsTiUwkmYNOBaQFShujKlyPDcqrf");
//	PlayingTable table("AbCdEsTiNOBaQFShujKlyPDUwkmY");
	PlayingTable table("AbCdEsTiUwkmYNOBaQFShujKlyPDcqrfGIHxWLMnopeRtgvV");
	table.notrump = false;
	table.trump = Suit::Clubs;
	table.declarer = (int)Compass::North;
	Trick t;
	time_t starttime = time(NULL);
	PlayingTable bestMoves = playAllTricksMinMax(table, -1, t, -1, NUMBER_OF_CARDS+1);
	std::cout << bestMoves.tricksWonByDeclaringSide << std::endl;
	std::cout << "All tricks:\n";
	for (int i = 0; i < NUMBER_OF_CARDS; i++)
	{
		std::cout << "Trick " << i << std::endl;
		std::cout << "Lead " << bestMoves.tricks[i].lead << std::endl;
		for (int j = 0; j < NUMBER_OF_PLAYERS; j++)
			std::cout << "Player " << j << " , Card: (" << bestMoves.tricks[i].trick[j] << ")\n";
	}
	//std::cout << "-------------------------" << std::endl;
	//for (int s = 0; s < NUMBER_OF_CARDS; s++)
	//{
	//	for (int i = 0; i < NUMBER_OF_CARDS; i++)
	//	{
	//		std::cout << "Trick " << i << std::endl;
	//		std::cout << "Lead " << tables[s].tricks[i].lead << std::endl;
	//		for (int j = 0; j < NUMBER_OF_PLAYERS; j++)
	//			std::cout << "Player " << j << " , Card: (" << tables[s].tricks[i].trick[j] << ")\n";
	//	}
	//	std::cout << "-------------------------" << std::endl;
	//}

	std::cout << "ClockTicks: " << difftime(time(NULL),starttime) << std::endl;
}
