
#pragma once

#include "game_board_defs.h"

// STL:
#include <tuple>
#include <string>

namespace JsonDecoder
{
	using JsonType = std::string;

	JsonType ConvertPlaceStoneCommand(const Stone& stone, const Position& position);

	JsonType ConvertChooseStoneCommand(const Stone& stone);

	JsonType ConvertGameStatus(GameStatus gameStatus, bool isComputer);

	std::tuple<Stone, Position> DecodePlaceStoneCommandFromJson(const std::string& json);

	Stone DecodeChooseStoneCommandFromJson(const std::string& json);
};
