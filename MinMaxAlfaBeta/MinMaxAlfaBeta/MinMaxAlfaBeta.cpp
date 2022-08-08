// MinMaxAlfaBeta.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"

Trick PlayingTable::playTrick()
{
	int numCardsLeft = NUMBER_OF_CARDS - trickCount;
	Card cardLed = playFirstCardinTrick();
	Trick trick;
	trick.lead = lead;
	trick.trick[0] = cardLed;
	for (int i = 0; i < NUMBER_OF_PLAYERS - 1; i++)
	{
		int player = (lead + i) % 4;
		Card cardPlayed = playNextCardinTrick(player, cardLed.suit);
		trick.trick[player] = cardPlayed;
	}
	return trick;
}

Card PlayingTable::playFirstCardinTrick()
{

}
Card PlayingTable::playNextCardinTrick(int player, Suit suitled)
{

}

