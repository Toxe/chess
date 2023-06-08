#pragma once

#include "../command/command.hpp"
#include "../game/player.hpp"
#include "../move_generator/game_state.hpp"

namespace chess {

class Board;
class CommandFactory;
class ConsoleWriter;

Command receive_ai_command(Player player, const Board& board, GameState game_state, const CommandFactory& command_factory, ConsoleWriter& console_writer);

}  // namespace chess
