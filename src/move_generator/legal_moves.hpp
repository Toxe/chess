#pragma once

#include "../board/board.hpp"
#include "game_state.hpp"
#include "moves.hpp"

namespace chess {

bool is_legal_move(Board& board, GameState game_state, Move move);
bool is_check(const Board& board, Player player);

}  // namespace chess
