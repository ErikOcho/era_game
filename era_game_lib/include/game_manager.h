/*!
	\brief  Manager that controls gameplay.
*/
#pragma once

#include "game_board.h"
#include "terminal_player.h"


class GameManager
{
public:
	GameManager();

	void RunGame(bool computerBegins = true);

private:
	void _PrintJsonMessageToConsole(const std::string& message);

	std::unique_ptr<IPlayer> _spFirstPlayer;
	std::unique_ptr<IPlayer> _spSecondPlayer;
	std::shared_ptr<GameBoard> _spGameBoard;

};
