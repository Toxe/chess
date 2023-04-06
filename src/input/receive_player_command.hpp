#pragma once

#include "../command/command.hpp"
#include "../game/player.hpp"

namespace chess {

class Board;
class ConsoleWriter;
class CommandFactory;

Command receive_player_command(Player player, Board& board, ConsoleWriter& console_writer, const CommandFactory& command_factory);

}  // namespace chess
