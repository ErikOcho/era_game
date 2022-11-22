/*!
	\brief Player class.
*/
#pragma once

#include "game_board.h" // TODO interface
#include "player_intf.h"

// STL:
#include <string>
#include <memory>


// Blocking player useingTerminal as interface. (In sense of waiting for his reaction. Meanwhile game is not running.)
class TerminalPlayer : public IPlayer
{
public:
	TerminalPlayer(const std::string& name, std::shared_ptr<GameBoard> _spGameBoard);

public:
	virtual Position PlaceStone(const Stone& stone) override;

	// Player chooses stone for opponent.
	virtual Stone ChooseStoneForOpponent() override;

	virtual std::string GetName() override;

private:
	std::shared_ptr<GameBoard> _spGameBoard;
	std::string _name;
};