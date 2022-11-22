// Class declaration.
#include "terminal_player.h"

#include "json_decoder.h"

// STL:
#include <iostream>
#include <string>
#include <cassert>


TerminalPlayer::TerminalPlayer(const std::string& name, std::shared_ptr<GameBoard> spGameBoard) : _name {name}, _spGameBoard{spGameBoard}
{
	assert(_spGameBoard);
}


std::string TerminalPlayer::GetName() 
{
	return _name;
}

Position TerminalPlayer::PlaceStone(const Stone& chosenStone)
{
	auto board {_spGameBoard->GetBoard()};
	// Make decision.
	std::string jsonMessage {};

	while(1) {
		std::cerr << "Place stone " << chosenStone << " on board. (Waiting for input.)" << std::endl;
		std::getline(std::cin, jsonMessage);

		try {
			auto [stone, position] {JsonDecoder::DecodePlaceStoneCommandFromJson(jsonMessage)};
			if (stone == chosenStone){
				return position;
			}
			else {
				std::cerr << "Cannot place different stone than chosen." << std::endl;
			}
		}
		catch (std::exception& e){
			std::cerr << "Catched exception while processing input: " << e.what() << std::endl;
			std::cout << "Invalid command. Please repeat." << std::endl;
		}
		catch (...){
			std::cerr << "Catched unknown exception while processing input. " << std::endl;
			std::cout << "Invalid command. Please repeat." << std::endl;
		}
	}

	return {}; // TODO
}

// Player chooses stone for opponent.
Stone TerminalPlayer::ChooseStoneForOpponent()
{
	auto remainingStones = _spGameBoard->GetRemainingStones();
	std::string jsonMessage {};

	while (true)
	{
		std::cerr << "Choose stone for opponent (Waiting for input.)" << std::endl;
		std::getline(std::cin, jsonMessage);
		try {
			auto stone {JsonDecoder::DecodeChooseStoneCommandFromJson(jsonMessage)};
			return stone;
		}
		catch (std::exception& e)
		{
			std::cerr << "Catched exception while processing input: " << e.what() << std::endl;
			std::cout << "Invalid command. Please repeat." << std::endl;
		}
		catch (...)
		{
			std::cerr << "Catched unknown exception while processing input. " << std::endl;
			std::cout << "Invalid command. Please repeat." << std::endl;
		}
	}

	return {}; // TODO
}

