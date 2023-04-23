#pragma once

#include "../board/square.hpp"
#include "../command/command.hpp"
#include "move.hpp"

namespace chess {

class Board;
class GamePlayers;
class ConsoleWriter;

Command PlayerMoveCommand(GamePlayers* game_players, Board* board, ConsoleWriter* console_writer, Move move);

}  // namespace chess
