#pragma once

#include "../board/square.hpp"
#include "../command/command.hpp"
#include "move.hpp"

namespace chess {

class Board;
class GamePlayers;
class ConsoleWriter;
struct GameState;

Command PlayerMoveCommand(Board* board, GameState* game_state, GamePlayers* game_players, ConsoleWriter* console_writer, Move move);

}  // namespace chess
