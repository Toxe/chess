#pragma once

#include "player.hpp"

namespace chess {

enum class PieceType : char {
    none = 0,
    pawn,
    knight,
    bishop,
    rook,
    queen,
    king
};

struct Piece {
    Player player;
    PieceType type;

    constexpr Piece(Player p, PieceType t) : player{p}, type{t} { }
    explicit Piece(char letter);

    bool operator==(const Piece& other) const = default;
    bool operator!=(const Piece& other) const = default;
};

constexpr Piece no_piece{Player::none, PieceType::none};

}  // namespace chess
