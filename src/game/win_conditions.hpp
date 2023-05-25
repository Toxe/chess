#pragma once

#include "../board/board.hpp"
#include "../game/player.hpp"
#include "../move_generator/game_state.hpp"

namespace chess {

enum class WinCondition {
    none,
    checkmate_white,  // black won
    checkmate_black,  // white won
    stalemate,
    fifty_move_rule,
};

[[nodiscard]] WinCondition get_win_condition(const Board& board, GameState game_state);
[[nodiscard]] bool game_over(WinCondition win_condition);
[[nodiscard]] bool is_checkmate(const Board& board, Player player);
[[nodiscard]] bool is_stalemate(const Board& board, Player player);
[[nodiscard]] bool is_fifty_move_rule(GameState game_state);

}  // namespace chess
