#include "moves.hpp"

#include <algorithm>

namespace chess {

int count_moves(const Moves& moves, const MoveType type)
{
    return static_cast<int>(std::count_if(moves.begin(), moves.end(), [=](const Move& move) { return move.type == type; }));
}

}  // namespace chess
