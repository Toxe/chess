#include "perft.hpp"

#include "../move_generator/legal_moves.hpp"
#include "../move_generator/list_moves.hpp"

namespace chess {

uint64_t perft(const Player player, Board& board, GameState game_state, PerftDivide& perft_divide, const int max_depth, const int depth)
{
    if (depth == max_depth)
        return 1;

    const Player opponent = opposing_player(player);
    const auto moves = list_moves(board, player);
    uint64_t total_moves = 0;

    for (const auto& move : moves) {
        if (is_legal_move(board, game_state, move)) {
            make_move(board, move);

            const uint64_t sub_moves = perft(opponent, board, update_game_state(game_state, move), perft_divide, max_depth, depth + 1);
            total_moves += sub_moves;

            if (depth == 0)
                perft_divide.add(move, sub_moves);

            undo_move(board, move);
        }
    }

    return total_moves;
}

}  // namespace chess
