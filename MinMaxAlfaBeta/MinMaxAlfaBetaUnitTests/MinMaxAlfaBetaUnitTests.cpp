#include "pch.h"
#include "CppUnitTest.h"
#include "..\MinMaxAlfaBeta\framework.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MinMaxAlfaBetaUnitTests
{
	TEST_CLASS(MinMaxAlfaBetaUnitTests)
	{
	public:
		
		TEST_METHOD(TestDeckWithLessThan52Cards)
		{
			Assert::ExpectException<std::domain_error>([]() -> void {PlayingTable table("abcdefghijklmnopqrstuvwxyz"); });
			
		}
		TEST_METHOD(TestDeckWithMoreThan52Cards)
		{
			Assert::ExpectException<std::domain_error>([]() -> void {PlayingTable table("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabc"); });

		}
		TEST_METHOD(TestDeckWithIllegalCard)
		{
			Assert::ExpectException<std::domain_error>([]() -> void {PlayingTable table("abcdefghijklmnopqrstuvwxyz0BCDEFGHIJKLMNOPQRSTUVWXYZ"); });

		}
		TEST_METHOD(TestDeckWith52CardsMonotoneIncreasing)
		{
			PlayingTable table("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
			for (int p = 0; p < NUMBER_OF_PLAYERS; p++)
				for (int c = 0; c < NUMBER_OF_CARDS; c++)
				{
					Assert::IsTrue(table.players[p].cards[c].card == Card((Suit)p, (CardValue)c));

				}
		}
		TEST_METHOD(TestDeckWith52CardsHalfwayMonotoneIncreasing)
		{
			PlayingTable table("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
			for (int p = 0; p < NUMBER_OF_PLAYERS; p++)
				for (int c = 0; c < NUMBER_OF_CARDS; c++)
				{
					int player = (p + 2) % 4;
					Assert::IsTrue(table.players[player].cards[c].card == Card((Suit)p, (CardValue)c));

				}
		}
		TEST_METHOD(TestDeckWhereEachPlayerHasOneSuitNoTrumpDeclarerNorth)
		{
			PlayingTable table("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
			table.declarer = (int) Compass::North;
			table.notrump = true;
			table.playAllTricks();
			Assert::IsTrue(table.trickCount == NUMBER_OF_CARDS);
			for (int i = 0; i < NUMBER_OF_CARDS; i++)
			{
				Assert::IsTrue(table.tricks[i].winner == (int)Compass::East);
				for (int j = 0; j < NUMBER_OF_PLAYERS; j++)
					Assert::IsTrue(table.players[j].cards[i].played);
			}
			Assert::IsTrue(table.tricksWonByDeclaringSide == 0);
		}
		TEST_METHOD(TestDeckWhereEachPlayerHasOneSuitNoTrumpDeclarerSouth)
		{
			PlayingTable table("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
			table.declarer = (int)Compass::South;
			table.notrump = true;
			table.playAllTricks();
			Assert::IsTrue(table.trickCount == NUMBER_OF_CARDS);
			for (int i = 0; i < NUMBER_OF_CARDS; i++)
			{
				Assert::IsTrue(table.tricks[i].winner == (int)Compass::West);
				for (int j = 0; j < NUMBER_OF_PLAYERS; j++)
					Assert::IsTrue(table.players[j].cards[i].played);
			}
			Assert::IsTrue(table.tricksWonByDeclaringSide == 0);
		}
		TEST_METHOD(TestDeckWhereEachPlayerHasOneSuitNoTrumpDeclarerWest)
		{
			PlayingTable table("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
			table.declarer = (int)Compass::West;
			table.notrump = true;
			table.playAllTricks();
			Assert::IsTrue(table.trickCount == NUMBER_OF_CARDS);
			for (int i = 0; i < NUMBER_OF_CARDS; i++)
			{
				Assert::IsTrue(table.tricks[i].winner == (int)Compass::North);
				for (int j = 0; j < NUMBER_OF_PLAYERS; j++)
					Assert::IsTrue(table.players[j].cards[i].played);
			}
			Assert::IsTrue(table.tricksWonByDeclaringSide == 0);

		}
		TEST_METHOD(TestDeckWhereEachPlayerHasOneSuitSpadesTrumpDeclarerNorth)
		{
			PlayingTable table("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
			table.declarer = (int)Compass::North;
			table.notrump = false;
			table.trump = Suit::Spades;
			table.playAllTricks();
			Assert::IsTrue(table.trickCount == NUMBER_OF_CARDS);
			for (int i = 0; i < NUMBER_OF_CARDS; i++)
			{
				Assert::IsTrue(table.tricks[i].winner == (int)Compass::South);
				for (int j = 0; j < NUMBER_OF_PLAYERS; j++)
					Assert::IsTrue(table.players[j].cards[i].played);
			}
			Assert::IsTrue(table.tricksWonByDeclaringSide == NUMBER_OF_CARDS);
		}
		TEST_METHOD(TestDeckWhereEachPlayerHasOneSuitClubsTrumpDeclarerNorth)
		{
			PlayingTable table("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
			table.declarer = (int)Compass::North;
			table.notrump = false;
			table.trump = Suit::Clubs;
			table.playAllTricks();
			Assert::IsTrue(table.trickCount == NUMBER_OF_CARDS);
			for (int i = 0; i < NUMBER_OF_CARDS; i++)
			{
				Assert::IsTrue(table.tricks[i].winner == (int)Compass::East);
				for (int j = 0; j < NUMBER_OF_PLAYERS; j++)
					Assert::IsTrue(table.players[j].cards[i].played);
			}
			Assert::IsTrue(table.tricksWonByDeclaringSide == 0);
		}
		TEST_METHOD(TestDeckWhereEachPlayerHasMinimalThreeCardsOfEachSuitNorthHighestNoTrump)
		{
			PlayingTable table("jklmxyzKLMXYZabcnopqABCNOPdefrstDEFGQRSghiuvwHIJTUVW");
			table.notrump = true;
			table.declarer = (int)Compass::North;
			table.playAllTricks();
			Assert::IsTrue(table.trickCount == NUMBER_OF_CARDS);
			for (int i = 0; i < NUMBER_OF_CARDS; i++)
			{
				Assert::IsTrue(table.tricks[i].winner == (int)Compass::North);
				for (int j = 0; j < NUMBER_OF_PLAYERS; j++)
					Assert::IsTrue(table.players[j].cards[i].played);
			}
			Assert::IsTrue(table.tricksWonByDeclaringSide == NUMBER_OF_CARDS);
		}

		TEST_METHOD(TestDeckWhereEachPlayerHasMinimalThreeCardsOfEachSuitNorthHighestDiamondsTrump)
		{
			PlayingTable table("jklmxyzKLMXYZabcnopqABCNOPdefrstDEFGQRSghiuvwHIJTUVW");
			table.notrump = false;
			table.trump = Suit::Diamonds;
			table.declarer = (int)Compass::North;
			table.playAllTricks();
			Assert::IsTrue(table.trickCount == NUMBER_OF_CARDS);
			for (int i = 0; i < NUMBER_OF_CARDS; i++)
			{
				Assert::IsTrue(table.tricks[i].winner == (int)Compass::North);
				for (int j = 0; j < NUMBER_OF_PLAYERS; j++)
					Assert::IsTrue(table.players[j].cards[i].played);
			}
			Assert::IsTrue(table.tricksWonByDeclaringSide == NUMBER_OF_CARDS);
		}
		TEST_METHOD(TestDeckWhereEachPlayerHasMinimalThreeCardsOfEachSuitNorthHighestSpadesTrump)
		{
			PlayingTable table("jklmxyzKLMXYZabcnopqABCNOPdefrstDEFGQRSghiuvwHIJTUVW");
			table.notrump = false;
			table.trump = Suit::Spades;
			table.declarer = (int)Compass::North;
			table.playAllTricks();
			Assert::IsTrue(table.trickCount == NUMBER_OF_CARDS);
			for (int i = 0; i < NUMBER_OF_CARDS; i++)
			{
				Assert::IsTrue(table.tricks[i].winner == (int)Compass::North || table.tricks[i].winner == (int)Compass::South);
				for (int j = 0; j < NUMBER_OF_PLAYERS; j++)
					Assert::IsTrue(table.players[j].cards[i].played);
			}
			Assert::IsTrue(table.tricksWonByDeclaringSide == NUMBER_OF_CARDS);
		}

	};
};

