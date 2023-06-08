#pragma once

#include "../command/command.hpp"
#include "../game/player.hpp"
#include "../move_generator/game_state.hpp"

namespace chess {

class Board;
class ConsoleWriter;
class CommandFactory;

Command receive_player_command(Player player, Board& board, GameState game_state, ConsoleWriter& console_writer, const CommandFactory& command_factory);

}  // namespace chess
