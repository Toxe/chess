#pragma once

#include <string_view>

#include "tl/expected.hpp"

#include "../command/command.hpp"
#include "../game/player.hpp"

namespace chess {

class Board;
class CommandFactory;

tl::expected<Command, std::string_view> eval_input(Player player, Board& board, const CommandFactory& command_factory, std::string_view input);

}  // namespace chess
