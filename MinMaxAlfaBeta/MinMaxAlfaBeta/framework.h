#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#define NUMBER_OF_CARDS 13
#define NUMBER_OF_PLAYERS 4
#define DECKSIZE (NUMBER_OF_PLAYERS * NUMBER_OF_CARDS)


enum class Suit
{
	Spades,
	Hearts,
	Diamonds,
	Clubs
};

enum class CardValue
{
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
	Ace
};

class Card
{
public:
	Card() : suit((Suit)0), value((CardValue)0)
	{
	}
	Card(Suit suit, CardValue value) : suit(suit),value(value)
	{
	}
	Suit suit;
	CardValue value;
};

bool operator == (Card c1, Card c2)
{
	return c1.suit == c2.suit && c1.value == c2.value;
}
bool operator != (Card c1, Card c2)
{
	return c1.suit != c2.suit || c1.value != c2.value;
}

class CardPlace
{
public:
	CardPlace() : card(Card()), played(false)
	{}
	CardPlace(Card c) : card(c), played(false)
	{}
	Card card;
	bool played;
private:
};

enum class Player
{
	North,
	East,
	South,
	West
};

class Hand
{
public:
	Hand()
	{}
	CardPlace cards[NUMBER_OF_CARDS];
};

class Trick
{
public:
	Trick() : lead(0)
	{}
	Card trick[NUMBER_OF_PLAYERS];
	int lead;
	int evaluate(Suit trump);
};

class PlayingTable
{
public:
	PlayingTable(std::string deal) : trump(Suit::Spades), notrump(false), declarer(0), lead(0), trickCount(0)
	{
		srand((unsigned int)time(NULL));
		if (deal.length() != DECKSIZE)
			throw std::domain_error("A deck should contain exactly 52 cards");
		for (int p = 0; p < NUMBER_OF_PLAYERS; p++)
			for (int i = 0; i < NUMBER_OF_CARDS; i++)
			{
				int cardNumber = p * NUMBER_OF_CARDS + i;
				int rawCardValue = isupper(deal[cardNumber]) ? deal[cardNumber] - 'A' : (islower(deal[cardNumber]) ? deal[cardNumber] - 'a' + (NUMBER_OF_CARDS*2) : throw std::domain_error("Illegal card in deck"));
				players[p].cards[i] = Card((Suit)(rawCardValue / 13), (CardValue)(rawCardValue % 13));
			}
	}
	Hand players[NUMBER_OF_PLAYERS];
	Suit trump;
	bool notrump;
	int declarer;
	int lead;
	int trickCount;
	Trick tricks[NUMBER_OF_CARDS];
	Trick playTrick();
	Card playFirstCardinTrick();
	Card playNextCardinTrick(int player, Suit suitLed);
	void playAllTricks();
private:

};


int randomCard(int numberOfCards)
{
	return rand() % numberOfCards;
}