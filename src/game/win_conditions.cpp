#include "win_conditions.hpp"

namespace chess {

WinCondition get_win_condition(const Board& board)
{
    if (check_player_victory(board, Player::white))
        return WinCondition::player1_won;

    if (check_player_victory(board, Player::black))
        return WinCondition::player2_won;

    return WinCondition::none;
}

bool game_over(const WinCondition win_condition)
{
    return win_condition != WinCondition::none;
}

bool check_player_victory(const Board& board, const Player player)
{
    return false;  // TODO
}

}  // namespace chess
