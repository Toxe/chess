#include "perft.hpp"

#include "../move_generator/list_moves.hpp"

namespace chess {

uint64_t perft(const Player player, Board& board, PerftDivide& perft_divide, const int max_depth, const int depth)
{
    if (depth == max_depth)
        return 1;

    const Player opponent = opposing_player(player);
    const auto moves = list_moves(player, board);

    uint64_t total_moves = 0;

    for (const auto& move : moves) {
        make_move(board, move);

        const uint64_t sub_moves = perft(opponent, board, perft_divide, max_depth, depth + 1);
        total_moves += sub_moves;

        undo_move(board, move);

        if (depth == 0)
            perft_divide.add(move.from, move.to, sub_moves);
    }

    return total_moves;
}

}  // namespace chess
