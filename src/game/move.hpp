#pragma once

#include "../board/square.hpp"
#include "pieces.hpp"

namespace chess {

enum class MoveType : char {
    normal = 0,
    capture,
    castling,
    en_passant,
    promotion,
};

struct Move {
    Square from;
    Square to;
    Piece piece;
    MoveType type;
};

}  // namespace chess
