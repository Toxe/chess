#pragma once

#include "../board/board.hpp"
#include "moves.hpp"

namespace chess {

// list all pseudo-legal moves
Moves list_moves(const Board& board, Player player);

}  // namespace chess
