/*!
	\brief Onterface for player object.
*/
#pragma once

#include "game_board_defs.h"


class IPlayer
{
public:
	// Virtual destructor.
	virtual ~IPlayer() = default;

	// Player chooses where to place given stone.
	virtual Position PlaceStone(const Stone& stone) = 0;

	// Player chooses stone for opponent.
	virtual Stone ChooseStoneForOpponent() = 0;

	virtual std::string GetName() = 0;
};
