/*
	\brief  Class representing game board.
*/

#include "game_board.h"

// STL:
#include <string>
#include <bitset>
#include <vector>
#include <algorithm>
#include <optional>
#include <iostream> 
#include <cassert>
#include <list>
#include <numeric>

static constexpr inline unsigned int dimension {4u};

// template<unsigned int Dim = 4>
// class Stone
// {
// 	using TProperties = std::bitset<Dim>;

// public:
// 	Stone(const std::string& propertiesString) : binaryProperties{propertiesString}
// 	{
// 		assert(propertiesString.size() <= Dim);
// 	}

// private:
// 	TProperties binaryProperties {};
// };


GameBoard::GameBoard() : _gameStatus{GameStatus::Playing}
{
	_board.resize(dimension, std::vector<std::optional<std::bitset<4>>>(dimension));
	_remaingStones = _GetAllStoneCombinations();
	assert(_remaingStones.size() == dimension * dimension);
	assert(_gameStatus == GameStatus::Playing);
	// Assert for nullopts on all positions.
}

bool GameBoard::TryToPutStone(const Stone &stone, const Position &position)
{
	bool stoneWasPlaced{false};

	if (_PositionIsFree(position))
	{
		if (auto stonePosition {_FindStoneAmongRemainingStones(stone)}; stonePosition != _remaingStones.cend()) {
		_board[position.x][position.y] = stone;
			_remaingStones.erase(stonePosition);
			_lastStonePosition = position;
			_UpdateGameStatus();
			stoneWasPlaced = true;
		}
		else {
			std::cerr << "The stone is allready on board. Cannot place two identical stones." << std::endl;
		}
	}
	else {
		std::cerr << "The spot ( " << position.x << ", " << position.y << ") is allready taken." << std::endl;
	}
	return stoneWasPlaced;
}

GameStatus GameBoard::GetGameStatus() const
{
	return _gameStatus;
}

Board GameBoard::GetBoard() const
{
	return _board;
}

std::list<Stone> GameBoard::GetRemainingStones() const
{
	return _remaingStones;
}

bool GameBoard::_PositionIsFree(const Position &position) const
{
	return !_board[position.x][position.y].has_value();
}

std::list<Stone>::const_iterator GameBoard::_FindStoneAmongRemainingStones(const Stone& stone) const
{
	return std::find(_remaingStones.cbegin(), _remaingStones.cend(), stone);
}

std::list<Stone> GameBoard::_GetAllStoneCombinations() const
{
	std::list<Stone> allStones{};
	constexpr std::size_t numberOfStones{dimension * dimension};
	for (std::size_t x{}; x < numberOfStones; ++x) {
		allStones.push_back(Stone((x >> 1) ^ x));
	}
	return allStones;
}

void GameBoard::_UpdateGameStatus()
{
	if (_gameStatus != GameStatus::Win) {
		if (_remaingStones.empty()) {
			_gameStatus = GameStatus::Tie;
			return;
		}
		// Check for win in row.
		auto &rowValues {_board[_lastStonePosition.x]};
		auto sameBitsRow {std::accumulate(rowValues.cbegin(), rowValues.cend(), Stone{"1111"}, [](const Stone &value, const std::optional<Stone> &stone)
						{ return stone.has_value() ? value & stone.value() : Stone {"0000"}; })};

		// Check for win in collumn.
		Stone sameBitsCollumn{"1111"};
		for (std::size_t i{}; i < dimension; ++i)
		{
			sameBitsCollumn = _board[i][_lastStonePosition.y].has_value() ? _board[i][_lastStonePosition.y].value() & sameBitsCollumn : Stone{"0000"};
		}

		// todo diagonaly.

		// 
		if ((sameBitsRow | sameBitsCollumn) != Stone{"0000"}){
			_gameStatus = GameStatus::Win;
		}
	}
}

