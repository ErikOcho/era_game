
#pragma once

#include "game_board_defs.h"
#include "game_board.h"

#include <memory>
#include <list>


class IGameBoardView
{
public:
	virtual ~IGameBoardView() = default;

	virtual std::list<Stone> GetRemainingStones() const = 0;

	virtual Board GetBoard() const = 0;
};

class GameBoardView : public IGameBoardView
{
public:
	GameBoardView(std::shared_ptr<GameBoard> spGameBoard) : _spGameBoard {spGameBoard} {}

	std::list<Stone> GetRemainingStones() const override { return _spGameBoard->GetRemainingStones(); }

	Board GetBoard() const override { return _spGameBoard->GetBoard(); }

private:
	std::shared_ptr<const GameBoard> _spGameBoard;
};
