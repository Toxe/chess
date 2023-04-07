#pragma once

#include "player.hpp"

namespace chess {

enum class PieceType {
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

    bool operator==(const Piece other) const { return other.player == player && other.type == type; }
    bool operator!=(const Piece other) const { return !(*this == other); }
};

constexpr Piece no_piece{Player::none, PieceType::none};

}  // namespace chess
