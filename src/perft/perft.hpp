#pragma once

#include <cstdint>

#include "../board/board.hpp"
#include "perft_divide.hpp"

namespace chess {

uint64_t perft(Player player, Board& board, PerftDivide& perft_divide, int max_depth, int depth = 0);

}  // namespace chess
