#pragma once

#include "../board/square.hpp"
#include "pieces.hpp"

namespace chess {

enum class MoveType : char {
    normal = 0,
    promotion,
    capture,
    capture_and_promotion,
    castling,
    en_passant
};

struct Move {
    Square from;
    Square to;
    Piece piece;
    MoveType type;

    bool operator==(const Move& other) const = default;
    bool operator!=(const Move& other) const = default;
};

}  // namespace chess
