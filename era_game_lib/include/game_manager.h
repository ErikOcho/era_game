/*!
	\brief  Manager that controls gameplay.
*/
#pragma once

#include "game_board.h"
#include "terminal_player.h"

#include <memory> // std::unique_ptr, ...

class GameManager
{
public:
	GameManager(std::unique_ptr<GameBoard> upGameBoard);

	void RunGame(bool computerBegins = true);

private:
	void _PrintJsonMessageToConsole(const std::string& message);

	bool _StoneIsAmongFreeStones(const Stone& stone);

	std::unique_ptr<IPlayer> _upFirstPlayer;
	std::unique_ptr<IPlayer> _upSecondPlayer;
	std::shared_ptr<GameBoard> _spGameBoard;
};
