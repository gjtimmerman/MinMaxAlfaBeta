#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#define NUMBER_OF_CARDS 13
#define NUMBER_OF_PLAYERS 4
#define DECKSIZE (NUMBER_OF_PLAYERS * NUMBER_OF_CARDS)


enum class Suit : char
{
	Spades,
	Hearts,
	Diamonds,
	Clubs
};

enum class CardValue : char
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

enum class Compass : char
{
	North,
	East,
	South,
	West
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

extern std::ostream& operator << (std::ostream& out, Card c);

extern bool operator == (Card c1, Card c2);
extern bool operator != (Card c1, Card c2);



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

enum class Player : char
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
	Trick() : lead(0), winner(0)
	{}
	Card trick[NUMBER_OF_PLAYERS];
	int lead;
	int winner;
	int evaluate(Suit trump, bool notrump);
};

class PlayingTable
{
public:
	PlayingTable() : trump(Suit::Spades), notrump(false), declarer(0), lead(0), trickCount(0), tricksWonByDeclaringSide(0)
	{

	}
	PlayingTable(std::string deal) : trump(Suit::Spades), notrump(false), declarer(0), lead(0), trickCount(0),tricksWonByDeclaringSide(0)
	{
		srand((unsigned int)time(NULL));
		if (deal.length() != DECKSIZE)
			throw std::domain_error("A deck should contain exactly 52 cards");
		for (int p = 0; p < NUMBER_OF_PLAYERS; p++)
			for (int i = 0; i < NUMBER_OF_CARDS; i++)
			{
				int cardNumber = p * NUMBER_OF_CARDS + i;
				int rawCardValue = isupper(deal[cardNumber]) ? deal[cardNumber] - 'A' : (islower(deal[cardNumber]) ? deal[cardNumber] - 'a' + 26 : throw std::domain_error("Illegal card in deck"));
				players[p].cards[i] = Card((Suit)(rawCardValue / 13), (CardValue)(rawCardValue % 13));
			}
	}
	Hand players[NUMBER_OF_PLAYERS];
	Suit trump;
	bool notrump;
	int declarer;
	int tricksWonByDeclaringSide;
	int lead;
	int trickCount;
	Trick tricks[NUMBER_OF_CARDS];
	Trick playTrick();
	Card playFirstCardinTrick();
	Card playNextCardinTrick(int player, Suit suitLed);
	void playAllTricks();
	PlayingTable evaluateScore(bool max, int &bestScoreSoFar, const PlayingTable &bestTableSoFar);
private:
};



extern PlayingTable playAllTricksMinMax(PlayingTable table,int player, Trick playedSoFar, int alfa, int beta);


