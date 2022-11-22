/*!
	\brief Unit tests for Class TerminalPlayer.
*/

// Tested files.
#include "terminal_player.h"

// Google Test support:
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// STL:

using namespace testing;


TEST(A, B) 
{
	std::shared_ptr<GameBoard> spBoard = std::make_shared<GameBoard>();
	TerminalPlayer player1 {"jozef:", spBoard};

	// auto position = player1.PlaceStone(Stone{"0001"});
	// auto chosenStone {player1.ChooseStoneForOpponent()};
}

#include "game_manager.h"

TEST(EraGame, Run)
{
	GameManager gm {};
	gm.RunGame();
}
