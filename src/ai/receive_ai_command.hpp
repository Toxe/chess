#pragma once

#include "../command/command.hpp"
#include "../game/player.hpp"

namespace chess {

class Board;
class CommandFactory;
class ConsoleWriter;

Command receive_ai_command(Player player, const Board& board, const CommandFactory& command_factory, ConsoleWriter& console_writer);

}  // namespace chess
