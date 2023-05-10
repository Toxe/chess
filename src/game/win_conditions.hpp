#pragma once

#include "../board/board.hpp"
#include "../game/player.hpp"

namespace chess {

enum class WinCondition {
    none,
    draw,
    checkmate_white,  // black won
    checkmate_black,  // white won
};

[[nodiscard]] WinCondition get_win_condition(const Board& board);
[[nodiscard]] bool game_over(WinCondition win_condition);
[[nodiscard]] bool is_checkmate(const Board& board, Player player);

}  // namespace chess
