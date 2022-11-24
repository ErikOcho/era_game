/*
	\brief  Class representing game board.
*/

#pragma once

#include "game_board_defs.h"

#include <list>
#include <cstddef>

class GameBoard
{
public:
	GameBoard();

	bool TryToPutStone(const Stone &stone, const Position &position);

	GameStatus GetGameStatus() const;

	Board GetBoard() const;

	std::list<Stone> GetRemainingStones() const;

private:
	bool _PositionIsFree(const Position &position) const;

	std::list<Stone>::const_iterator _FindStoneAmongRemainingStones(const Stone &stone) const;

	std::list<Stone> _GetAllStoneCombinations() const;

	void _UpdateGameStatus();

private:
	// First of the pair is the first player.
	// std::pair<std::string, std::string> _playerNames{};
	Board _board {};
	std::list<Stone> _remaingStones{};
	GameStatus _gameStatus{};
	Position _lastStonePosition{};
};
