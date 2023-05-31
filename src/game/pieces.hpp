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

PieceType piece_type_from_char(char c);

struct Piece {
    Player player;
    PieceType type;

    constexpr Piece(Player p, PieceType t) : player{p}, type{t} { }
    explicit Piece(char c) : player{player_from_char(c)}, type{piece_type_from_char(c)} { }
    Piece(Player p, char c) : player{p}, type{piece_type_from_char(c)} { }

    bool operator==(const Piece& other) const = default;
    bool operator!=(const Piece& other) const = default;
};

constexpr Piece no_piece{Player::none, PieceType::none};

}  // namespace chess
