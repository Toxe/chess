#pragma once

#include "../board/square.hpp"
#include "pieces.hpp"

namespace chess {

struct Move {
    Square from;
    Square to;
    Piece piece;
};

}  // namespace chess
