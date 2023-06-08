#pragma once

#include "../board/board.hpp"
#include "game_state.hpp"
#include "moves.hpp"

namespace chess {

enum class MoveLegality {
    ok,
    en_passant_target_square_not_set,
    en_passant_target_square_wrong,
    check,
    would_result_in_check,
    square_under_attack,
    no_castling_ability,
};

[[nodiscard]] MoveLegality check_legal_move(Board& board, GameState game_state, Move move);
[[nodiscard]] bool is_check(const Board& board, Player player);

}  // namespace chess
