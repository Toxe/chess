#pragma once
#pragma once

#include <string>

#include "board.hpp"

namespace chess {

enum class BoardPrintFormat {
    simple,
    unicode,
};

std::string print_square(Square square);
std::string print_board(const Board& board, BoardPrintFormat format);

}  // namespace chess
