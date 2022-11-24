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
	DumbPlayer(const std::string& name, std::shared_ptr<GameBoardView> spGameBoard) : _name {name}, _spGameBoardView{spGameBoard}
	{
		assert(_spGameBoardView);
	}

public:
	virtual Position PlaceStone(const Stone& stone) override
	{
		auto board {_spGameBoardView->GetBoard()};
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
		return _spGameBoardView->GetRemainingStones().front();
	}

	virtual std::string GetName() override
	{
		return _name;
	}

private:
	std::shared_ptr<GameBoardView> _spGameBoardView;
	std::string _name;
};


GameManager::GameManager(std::unique_ptr<GameBoard> upGameBoard) : _spGameBoard {std::move(upGameBoard)}
{}


void GameManager::RunGame(bool computerBegins)
{
	// Making shared_ptr from unique.
	auto spGameBoardView = std::make_shared<GameBoardView>(_spGameBoard);

	// Create players.
	if (computerBegins) {
		_upFirstPlayer = std::make_unique<DumbPlayer>("Computer", spGameBoardView);
		_upSecondPlayer = std::make_unique<TerminalPlayer>("Player", spGameBoardView);
	}
	else {
		_upSecondPlayer = std::make_unique<DumbPlayer>("Computer", spGameBoardView);
		_upFirstPlayer = std::make_unique<TerminalPlayer>("Player", spGameBoardView);
	}

	Stone stoneForOpponent {};
	Position position {};
	
	while (_spGameBoard->GetGameStatus() == GameStatus::Playing)
	{
		while (true) {
			stoneForOpponent = _upFirstPlayer->ChooseStoneForOpponent();
			if (_StoneIsAmongFreeStones(stoneForOpponent)){
				break;
			}
		}
		if (_upFirstPlayer->GetName() == "Computer") {
			_PrintJsonMessageToConsole(JsonDecoder::ConvertChooseStoneCommand(stoneForOpponent));
		}

		while (true) {
			position = _upSecondPlayer->PlaceStone(stoneForOpponent);
			if (_spGameBoard->TryToPutStone(stoneForOpponent, {position.x - 1, position.y - 1})) {
				break;
			}
		}
		if (_upFirstPlayer->GetName() == "Computer") {
			_PrintJsonMessageToConsole(JsonDecoder::ConvertPlaceStoneCommand(stoneForOpponent, position));
		}
		_PrintJsonMessageToConsole(JsonDecoder::ConvertGameStatus(_spGameBoard->GetGameStatus(), _upSecondPlayer->GetName() == "Computer"));

		std::swap(_upFirstPlayer, _upSecondPlayer);
	}

}

void GameManager::_PrintJsonMessageToConsole(const std::string & message)
{
	std::cout << message << std::endl;
}

bool GameManager::_StoneIsAmongFreeStones(const Stone & stone)
{
	auto remainingStones = _spGameBoard->GetRemainingStones();
	if (std::find(remainingStones.cbegin(), remainingStones.cend(), stone) != remainingStones.cend())
	{
		return false;
	}
	return true;
}
