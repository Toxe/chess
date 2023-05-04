#pragma once

#include <optional>

#include "../board/board.hpp"
#include "../game/move.hpp"

namespace chess {

std::optional<Move> generate_move(const Board& board, Player player);

}  // namespace chess
