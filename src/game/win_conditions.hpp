#pragma once

#include "../board/board.hpp"
#include "../game/player.hpp"

namespace chess {

enum class WinCondition {
    none,
    checkmate_white,  // black won
    checkmate_black,  // white won
    stalemate,
};

[[nodiscard]] WinCondition get_win_condition(const Board& board);
[[nodiscard]] bool game_over(WinCondition win_condition);
[[nodiscard]] bool is_checkmate(const Board& board, Player player);
[[nodiscard]] bool is_stalemate(const Board& board, Player player);

}  // namespace chess
