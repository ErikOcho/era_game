/*!
	\brief Definitions for GameBoard class.
*/
#pragma once

#include <string>
#include <bitset>
#include <vector>
#include <optional>
#include <list>

// Position on board. x is index of row any y index of collumn.
struct Position
{
	int x;
	int y;
};

// Enum defining game status.
enum class GameStatus
{
	Playing,  // Still playing.
	Win,      // One of the players have won.
	Tie       // Game ended.
};

/*
	Type for declaring stone with its properties. (Properties are defined using binary 0/1 form.)
	Now we have 4 binary properties. (FOr example color: blue/red, shape(round, square), ...)
*/
using Stone = std::bitset<4>;

/*
	Type defining board status. Nullopt means that there is no stone placed on board.
*/
using Board = std::vector<std::vector<std::optional<Stone>>>;

