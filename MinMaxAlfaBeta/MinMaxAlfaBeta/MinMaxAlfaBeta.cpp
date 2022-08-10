// MinMaxAlfaBeta.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"

bool operator == (Card c1, Card c2)
{
	return c1.suit == c2.suit && c1.value == c2.value;
}
bool operator != (Card c1, Card c2)
{
	return c1.suit != c2.suit || c1.value != c2.value;
}

extern std::ostream& operator << (std::ostream& out, Card c)
{
	switch (c.suit)
	{
	case Suit::Spades:
		out << "S";
		break;
	case Suit::Hearts:
		out << "H";
		break;
	case Suit::Diamonds:
		out << "D";
		break;
	case Suit::Clubs:
		out << "C";
		break;
	}
	switch (c.value)
	{
	case CardValue::Ace:
		out << "A";
		break;
	case CardValue::King:
		out << "K";
		break;
	case CardValue::Queen:
		out << "Q";
		break;
	case CardValue::Jack:
		out << "J";
		break;
	case CardValue::Ten:
		out << "T";
		break;
	default:
		out << (char)(((int)c.value) + 2 + '0');
		break;
	}
	return out;
}


int randomCard(int numberOfCards)
{
	return rand() % numberOfCards;
}

int Trick::evaluate(Suit trump, bool notrump)
{
	if (!notrump)
	{
		winner = -1;
		for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
			if (trick[i].suit == trump)
			{
				winner = i;
				break;
			}
		if (winner >= 0)
		{
			for (int i = winner + 1; i < NUMBER_OF_PLAYERS; i++)
				if (trick[i].suit == trump && trick[i].value > trick[winner].value)
					winner = i;
			return winner;
		}
	}
	winner = lead;
	for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		if (i == lead)
			continue;
		if (trick[i].suit == trick[lead].suit && trick[i].value > trick[winner].value)
			winner = i;
	}
	return winner;
}

Trick PlayingTable::playTrick()
{
	Card cardLed = playFirstCardinTrick();
	Trick trick;
	trick.lead = lead;
	trick.trick[lead] = cardLed;
	for (int i = 1; i < NUMBER_OF_PLAYERS; i++)
	{
		int player = (lead + i) % 4;
		Card cardPlayed = playNextCardinTrick(player, cardLed.suit);
		trick.trick[player] = cardPlayed;
	}
	return trick;
}

Card PlayingTable::playFirstCardinTrick()
{
	int numCardsLeft = NUMBER_OF_CARDS - trickCount;
	int cardToPlay = randomCard(numCardsLeft);
	int cardSelector = 0;
	for (int i = 0; i < NUMBER_OF_CARDS; i++)
	{
		if (!players[lead].cards[i].played)
			if (cardSelector++ == cardToPlay)
			{
				players[lead].cards[i].played = true;
				return players[lead].cards[i].card;
			}
	}
	throw std::domain_error("This should never happen!");
}

PlayingTable PlayingTable::evaluateScore(bool max, int &bestScoreSoFar,const PlayingTable &bestTableSoFar)
{
	if (max)
	{
		if (tricksWonByDeclaringSide > bestScoreSoFar)
		{
			bestScoreSoFar = tricksWonByDeclaringSide;
			return *this;
		}
	}
	else
		if (tricksWonByDeclaringSide < bestScoreSoFar)
		{
			bestScoreSoFar = tricksWonByDeclaringSide;
			return *this;
		}
	return bestTableSoFar;
}

Card PlayingTable::playNextCardinTrick(int player, Suit suitled)
{
	int numCardsLeft = NUMBER_OF_CARDS - trickCount;
	int numCardsLeftinSuitLed = 0;
	for (int i = 0; i < NUMBER_OF_CARDS; i++)
	{
		if (!players[player].cards[i].played && players[player].cards[i].card.suit == suitled)
			numCardsLeftinSuitLed++;
	}
	if (numCardsLeftinSuitLed > 0)
	{
		int cardToPlay = randomCard(numCardsLeftinSuitLed);
		int cardSelector = 0;
		for (int i = 0; i < NUMBER_OF_CARDS; i++)
			if (!players[player].cards[i].played && players[player].cards[i].card.suit == suitled)
				if (cardSelector++ == cardToPlay)
				{
					players[player].cards[i].played = true;
					return players[player].cards[i].card;
				}
	}
	else
	{
		int cardToPlay = randomCard(numCardsLeft);
		int cardSelector = 0;
		for (int i = 0; i < NUMBER_OF_CARDS; i++)
			if (!players[player].cards[i].played)
				if (cardSelector++ == cardToPlay)
				{
					players[player].cards[i].played = true;
					return players[player].cards[i].card;
				}
	}
	throw std::domain_error("This should never happen!");
}

void PlayingTable::playAllTricks()
{
	lead = (declarer + 1) % 4;

	for (trickCount = 0; trickCount < NUMBER_OF_CARDS; trickCount++)
	{
		tricks[trickCount] = playTrick();
		lead = tricks[trickCount].evaluate(trump, notrump);
		if (tricks[trickCount].winner % 2 == declarer % 2)
			tricksWonByDeclaringSide++;
	}
}

PlayingTable playAllTricksMinMax(PlayingTable table,int player,Trick playedSoFar, int alfa, int beta)
{
	if (player == table.lead)	// Trick completed
	{
		table.lead = playedSoFar.evaluate(table.trump,table.notrump);
		if (playedSoFar.winner % 2 == table.declarer % 2)
			table.tricksWonByDeclaringSide++;
		table.tricks[table.trickCount++] = playedSoFar;
		if (table.trickCount == NUMBER_OF_CARDS)		// Game completed
		{
			return table;
		}
		PlayingTable bestTableSoFar;
		bool max = (table.lead % 2) == (table.declarer % 2);
		int bestScoreSoFar = max ? -1 : NUMBER_OF_CARDS + 1;
		for (int i = 0; i < NUMBER_OF_CARDS; i++)
		{
			Trick newTrick;
			newTrick.lead = table.lead;
			if (!table.players[table.lead].cards[i].played)
			{
				newTrick.trick[table.lead] = table.players[table.lead].cards[i].card;
				table.players[table.lead].cards[i].played = true;
				PlayingTable t = playAllTricksMinMax(table, (table.lead + 1) % NUMBER_OF_PLAYERS, newTrick, alfa, beta);
						
				table.players[table.lead].cards[i].played = false;
				bestTableSoFar = t.evaluateScore(max, bestScoreSoFar, bestTableSoFar);
				if (max)
				{
					if (bestScoreSoFar > alfa)
						alfa = bestScoreSoFar;
				}
				else
				{
					if (bestScoreSoFar < beta)
						beta = bestScoreSoFar;
				}
				if (alfa >= beta)
					return bestTableSoFar;
			}
		}
		return bestTableSoFar;
	}
	else if (player >= 0)		// player is not lead and not start of game
	{
		PlayingTable bestTableSoFar;
		bool max = (player % 2) == (table.declarer % 2);
		int bestScoreSoFar = max ? -1 : NUMBER_OF_CARDS + 1;
		int firstCardinSuitLed = -1;
		Suit suitLed = playedSoFar.trick[playedSoFar.lead].suit;
		for (int i = 0; i < NUMBER_OF_CARDS; i++)
			if (!table.players[player].cards[i].played && table.players[player].cards[i].card.suit == suitLed)
				firstCardinSuitLed = i;
		if (firstCardinSuitLed >= 0)		// player has card in suitLed, so must follow the leader
		{
			for (int i = firstCardinSuitLed; i < NUMBER_OF_CARDS; i++)
				if (!table.players[player].cards[i].played && table.players[player].cards[i].card.suit == suitLed)
				{
					playedSoFar.trick[player] = table.players[player].cards[i].card;
					table.players[player].cards[i].played = true;

					PlayingTable t = playAllTricksMinMax(table, (player + 1) % NUMBER_OF_PLAYERS, playedSoFar, alfa, beta);
					bestTableSoFar = t.evaluateScore(max, bestScoreSoFar, bestTableSoFar);
					table.players[player].cards[i].played = false;
					if (max)
					{
						if (bestScoreSoFar > alfa)
							alfa = bestScoreSoFar;
					}
					else
					{
						if (bestScoreSoFar < beta)
							beta = bestScoreSoFar;
					}
					if (alfa >= beta)
						return bestTableSoFar;

				}
			return bestTableSoFar;
		}
		else					// player has no card in suitLed, may play any card
		{
			for (int i = 0; i < NUMBER_OF_CARDS; i++)
				if (!table.players[player].cards[i].played)
				{
					playedSoFar.trick[player] = table.players[player].cards[i].card;
					table.players[player].cards[i].played = true;
					PlayingTable t = playAllTricksMinMax(table, (player + 1) % NUMBER_OF_PLAYERS, playedSoFar, alfa, beta);
					bestTableSoFar = t.evaluateScore(max, bestScoreSoFar, bestTableSoFar);
					table.players[player].cards[i].played = false;
					if (max)
					{
						if (bestScoreSoFar > alfa)
							alfa = bestScoreSoFar;
					}
					else
					{
						if (bestScoreSoFar < beta)
							beta = bestScoreSoFar;
					}
					if (alfa >= beta)
						return bestTableSoFar;

				}
			return bestTableSoFar;
		}
	}
	else		// start of game
	{
		table.lead = (table.declarer + 1) % NUMBER_OF_PLAYERS;
		PlayingTable bestTableSoFar;
		bool max = (table.lead % 2) == (table.declarer % 2);
		int bestScoreSoFar = max ? -1 : NUMBER_OF_CARDS + 1;

		for (int i = 0; i < NUMBER_OF_CARDS; i++)
		{
			Trick newTrick;
			newTrick.lead = table.lead;

			if (!table.players[table.lead].cards[i].played)
			{
				newTrick.trick[table.lead] = table.players[table.lead].cards[i].card;
				table.players[table.lead].cards[i].played = true;
				PlayingTable t = playAllTricksMinMax(table, (table.lead + 1) % NUMBER_OF_PLAYERS, newTrick, alfa, beta);
				bestTableSoFar = t.evaluateScore(max, bestScoreSoFar, bestTableSoFar);

				table.players[table.lead].cards[i].played = false;
				if (max)
				{
					if (bestScoreSoFar > alfa)
						alfa = bestScoreSoFar;
				}
				else
				{
					if (bestScoreSoFar < beta)
						beta = bestScoreSoFar;
				}
				if (alfa >= beta)
					return bestTableSoFar;

			}

		}
		return bestTableSoFar;

		
	}

}


