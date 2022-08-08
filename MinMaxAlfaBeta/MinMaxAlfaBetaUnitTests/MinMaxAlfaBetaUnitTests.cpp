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
	};
};

