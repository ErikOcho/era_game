/*!
	\brief Tests for the class GameBoard.
*/

// Tested files.
#include "game_board.h"

// Google Test support:
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// STL:
#include <algorithm>    // std::for_each


using namespace testing;


struct GameBoardTest : public Test
{
};

TEST(GameBoardBasicTests, Construction)
{
	GameBoard gameBoard{};

	// Testing empty board and status.
	EXPECT_EQ(gameBoard.GetGameStatus(), GameStatus::Playing);
	EXPECT_THAT(
		gameBoard.GetBoard(), ElementsAre(
								  ElementsAre(Eq(std::nullopt), Eq(std::nullopt), Eq(std::nullopt), Eq(std::nullopt)),
								  ElementsAre(Eq(std::nullopt), Eq(std::nullopt), Eq(std::nullopt), Eq(std::nullopt)),
								  ElementsAre(Eq(std::nullopt), Eq(std::nullopt), Eq(std::nullopt), Eq(std::nullopt)),
								  ElementsAre(Eq(std::nullopt), Eq(std::nullopt), Eq(std::nullopt), Eq(std::nullopt))
							  )
	);
}

// Testing valid placement of stone.
TEST(GameBoardBasicTests, TryToPutStoneToEmptyPosition)
{
	GameBoard gameBoard{};

	// Testing empty board and status.
	EXPECT_THAT(
		gameBoard.GetRemainingStones(),
		UnorderedElementsAreArray(
			{Stone("0000"), Stone("0001"), Stone("0010"), Stone("0100"), Stone("1000"), Stone("0011"), Stone("0101"), Stone("1001"), Stone("0110"),
			 Stone("1010"), Stone("1100"), Stone("0111"), Stone("1011"), Stone("1101"), Stone("1110"), Stone("1111")}
		)
	);

	// Testing that placement of stone deletes the stone from remaining ones.
	ASSERT_TRUE(gameBoard.TryToPutStone(Stone{"1111"}, {0, 0}));
	EXPECT_THAT(gameBoard.GetRemainingStones(),
				Not(Contains(Stone{"1111"})));
}

// Testing function of showing remaining stones.
TEST(GameBoardBasicTests, RemainingStones)
{
	GameBoard gameBoard{};

	// Testing empty board and status.
	EXPECT_THAT(
		gameBoard.GetRemainingStones(),
		UnorderedElementsAreArray(
			{
				Stone("0000"), Stone("0001"), Stone("0010"), Stone("0100"),
				Stone("1000"), Stone("0011"), Stone("0101"), Stone("1001"),
				Stone("0110"), Stone("1010"), Stone("1100"), Stone("0111"),
				Stone("1011"), Stone("1101"), Stone("1110"), Stone("1111")
			}
		)
	);

	// Testing that placement of stone deletes the stone from remaining ones.
	ASSERT_TRUE(gameBoard.TryToPutStone(Stone{"1111"}, {0, 0}));
	EXPECT_THAT(gameBoard.GetRemainingStones(), Not(Contains(Stone {"1111"})));
}

// Choose spots in a way than no one wins.
TEST(GameBoardBasicTest, WinFullBoard)
{
	GameBoard gameBoard{};
	auto remainingStones {gameBoard.GetRemainingStones()};
	std::vector<Stone> remainingStonesVector{remainingStones.begin(), remainingStones.end()};
	std::vector<Position> positions {
		{0, 0}, {0, 1}, {0, 2}, {0, 3},
		{1, 0}, {1, 1}, {1, 2}, {1, 3},
		{2, 0}, {2, 1}, {2, 2}, {2, 3},
		{3, 0}, {3, 1}, {3, 2}, {3, 3}
	};
	for (std::size_t i {}; i < positions.size(); ++i){
		EXPECT_TRUE(gameBoard.TryToPutStone(remainingStonesVector[i], positions[i]));
	}

	EXPECT_EQ(gameBoard.GetGameStatus(), GameStatus::Win); // Should be Tie.
}

