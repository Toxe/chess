#include "win_conditions.hpp"

#include <algorithm>

#include "../move_generator/legal_moves.hpp"
#include "../move_generator/list_moves.hpp"

namespace chess {

WinCondition get_win_condition(const Board& board)
{
    if (is_checkmate(board, Player::white))
        return WinCondition::checkmate_white;

    if (is_checkmate(board, Player::black))
        return WinCondition::checkmate_black;

    return WinCondition::none;
}

bool game_over(const WinCondition win_condition)
{
    return win_condition != WinCondition::none;
}

bool is_checkmate(const Board& board, const Player player)
{
    Board board_copy = board;
    GameState game_state;
    const auto moves = list_moves(board_copy, player);

    return std::none_of(moves.begin(), moves.end(), [&](const Move& move) { return is_legal_move(board_copy, game_state, move); });
}

}  // namespace chess
