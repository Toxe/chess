#include "move_generator.hpp"

#include "list_moves.hpp"

namespace chess {

std::optional<Move> generate_move(const Board& board, const Player player)
{
    const auto moves = list_moves(board, player);

    if (moves.empty())
        return {};

    return moves.front();
}

}  // namespace chess
