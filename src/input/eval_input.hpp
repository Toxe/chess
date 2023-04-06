#pragma once

#include <optional>
#include <string>

#include "../command/command.hpp"
#include "../game/player.hpp"

namespace chess {

class Board;
class CommandFactory;

std::optional<Command> eval_input(Player player, Board& board, const CommandFactory& command_factory, const std::string& input);

}  // namespace chess
