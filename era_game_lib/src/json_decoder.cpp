
#include "json_decoder.h"
#include "json.hpp"

namespace JsonDecoder
{

JsonType ConvertPlaceStoneCommand(const Stone& stone, const Position& position)
{
	nlohmann::json j;
	j["stone"] = stone.to_string();
	j["field"] = (position.x * 10) + position.y;

	return j.dump();
}

JsonType ConvertChooseStoneCommand(const Stone& stone)
{
	nlohmann::json j;
	j["chosen_stone"] = stone.to_string();

	return j.dump();
}

JsonType ConvertGameStatus(GameStatus gameStatus, bool isComputer)
{
	std::string statusName {};
	if (gameStatus == GameStatus::Playing){
		statusName = "playing";
	}
	else if (gameStatus == GameStatus::Tie) {
		statusName = "playing";
	}
	else if (gameStatus == GameStatus::Win){
		if (isComputer) {
			statusName = "computer wins";
		}
		else {
			statusName = "player wins";
		}
	}

	nlohmann::json j;
	j["status"] = statusName;

	return j.dump();
}

std::tuple<Stone,Position> DecodePlaceStoneCommandFromJson(const std::string & json)
{
	nlohmann::json j {nlohmann::json::parse(json)};
	std::string stoneString = j["stone"];
	Stone stone {stoneString};
	int fieldInt = j["field"];
	Position pos {fieldInt / 10, fieldInt % 10};

	return {stone, pos};
}

Stone DecodeChooseStoneCommandFromJson(const std::string & json)
{
	nlohmann::json j {nlohmann::json::parse(json)};
	std::string stoneString = j["chosen_stone"];

	return Stone {stoneString};
}


}