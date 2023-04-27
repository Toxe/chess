#pragma once

#include <vector>

#include "../board/board.hpp"
#include "../game/move.hpp"

namespace chess {

using Moves = std::vector<Move>;

// list all pseudo-legal moves
Moves list_moves(const Board& board);

}  // namespace chess
