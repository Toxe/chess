#pragma once

#include <string>

#include "board.hpp"

namespace chess {

std::string print_square(Square square);
std::string print_board(const Board& board);

}  // namespace chess
