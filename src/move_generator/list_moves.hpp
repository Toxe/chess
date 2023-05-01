#pragma once

#include "../board/board.hpp"
#include "moves.hpp"

namespace chess {

// list all pseudo-legal moves
Moves list_moves(Player player, const Board& board);

}  // namespace chess
