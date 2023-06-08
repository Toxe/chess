#include "win_conditions.hpp"

#include <algorithm>

#include "../move_generator/legal_moves.hpp"
#include "../move_generator/list_moves.hpp"

namespace chess {

WinCondition get_win_condition(const Board& board, const GameState game_state)
{
    if (is_checkmate(board, Player::white))
        return WinCondition::checkmate_white;

    if (is_checkmate(board, Player::black))
        return WinCondition::checkmate_black;

    if (is_stalemate(board, Player::white))
        return WinCondition::stalemate;

    if (is_stalemate(board, Player::black))
        return WinCondition::stalemate;

    if (is_fifty_move_rule(game_state))
        return WinCondition::fifty_move_rule;

    return WinCondition::none;
}

bool game_over(const WinCondition win_condition)
{
    return win_condition != WinCondition::none;
}

bool is_checkmate(const Board& board, const Player player)
{
    if (!is_check(board, player))
        return false;

    Board board_copy = board;
    GameState game_state;
    const auto moves = list_moves(board_copy, player);

    return std::none_of(moves.begin(), moves.end(), [&](const Move& move) { return check_legal_move(board_copy, game_state, move) == MoveLegality::ok; });
}

bool is_stalemate(const Board& board, const Player player)
{
    if (is_check(board, player))
        return false;

    Board board_copy = board;
    GameState game_state;
    const auto moves = list_moves(board_copy, player);

    return std::none_of(moves.begin(), moves.end(), [&](const Move& move) { return check_legal_move(board_copy, game_state, move) == MoveLegality::ok; });
}

bool is_fifty_move_rule(const GameState game_state)
{
    return game_state.halfmove_clock >= 50;
}

}  // namespace chess
