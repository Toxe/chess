#pragma once

#include <vector>

#include "../game/move.hpp"

namespace chess {

using Moves = std::vector<Move>;

int count_moves(const Moves& moves, MoveType type);

}  // namespace chess
