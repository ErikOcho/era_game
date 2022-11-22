/*!
	\brief Game manager class. Controls whole game with logging of moves to console.
*/

#include "game_manager.h"
#include "json_decoder.h"

// STL:
#include <string>
#include <iostream>


class DumbPlayer : public IPlayer
{
public:
	DumbPlayer(const std::string& name, std::shared_ptr<GameBoard> spGameBoard) : _name {name}, _spGameBoard{spGameBoard}
	{
		assert(_spGameBoard);
	}

public:
	virtual Position PlaceStone(const Stone& stone) override
	{
		auto board {_spGameBoard->GetBoard()};
		for (std::size_t i {}; i < board.size(); ++i){
			for (std::size_t j {}; j < board.size(); ++j) {
				if (!board[i][j].has_value()) {
					return {int(i + 1), int(j + 1)};
				}
			}
		}
		return {};
	}

	// Player chooses stone for opponent.
	virtual Stone ChooseStoneForOpponent() override
	{
		return _spGameBoard->GetRemainingStones().front();
	}

	virtual std::string GetName() override
	{
		return _name;
	}

private:
	std::shared_ptr<GameBoard> _spGameBoard;
	std::string _name;
};


GameManager::GameManager()
{}

void GameManager::RunGame(bool computerBegins)
{
	// Make game board.
	auto spGameBoard = std::make_shared<GameBoard>();

	// Create players.
	if (computerBegins) {
		_spFirstPlayer = std::make_unique<DumbPlayer>("Computer", spGameBoard);
		_spSecondPlayer = std::make_unique<TerminalPlayer>("Player", spGameBoard);
	}
	else {
		_spSecondPlayer = std::make_unique<DumbPlayer>("Computer", spGameBoard);
		_spFirstPlayer = std::make_unique<TerminalPlayer>("Player", spGameBoard);
	}



	Stone stoneForOpponent {};
	Position position {};
	// {"stone": "0000", "field": 21}
	// {"stone": "0110", "field": 22}
	// {"chosen_stone":"0011"}
	// {"chosen_stone":"0011"}
	while (spGameBoard->GetGameStatus() == GameStatus::Playing)
	{
		while (true) {
			stoneForOpponent = _spFirstPlayer->ChooseStoneForOpponent();
			auto remainingStones = spGameBoard->GetRemainingStones();
			if (std::find(remainingStones.cbegin(), remainingStones.cend(), stoneForOpponent) != remainingStones.cend()){
				break;
			}
		}
		_PrintJsonMessageToConsole(JsonDecoder::ConvertChooseStoneCommand(stoneForOpponent));

		while (true) {
			position = _spSecondPlayer->PlaceStone(stoneForOpponent);
			if (spGameBoard->TryToPutStone(stoneForOpponent, {position.x - 1, position.y - 1})) {
				break;
			}
		}
		_PrintJsonMessageToConsole(JsonDecoder::ConvertPlaceStoneCommand(stoneForOpponent, position));
		_PrintJsonMessageToConsole(JsonDecoder::ConvertGameStatus(spGameBoard->GetGameStatus(), _spSecondPlayer->GetName() == "Computer"));

		std::swap(_spFirstPlayer, _spSecondPlayer);
	}
}

void GameManager::_PrintJsonMessageToConsole(const std::string & message)
{
	std::cout << message << std::endl;
}
