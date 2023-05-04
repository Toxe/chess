#pragma once

#include <cstdint>

#include "../board/board.hpp"
#include "../move_generator/game_state.hpp"
#include "perft_divide.hpp"

namespace chess {

uint64_t perft(Player player, Board& board, GameState game_state, PerftDivide& perft_divide, int max_depth, int depth = 0);

}  // namespace chess
