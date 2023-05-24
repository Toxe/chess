#pragma once

#include "../board/board.hpp"
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
    Piece captured_piece;
    MoveType type;

    static Move create_normal(Square move_from, Square move_to, Piece moved_piece);
    static Move create_promotion(Square move_from, Square move_to, Piece promoted_piece);
    static Move create_capture(Square move_from, Square move_to, Piece moved_piece, Piece opposing_piece);
    static Move create_capture_and_promotion(Square move_from, Square move_to, Piece promoted_piece, Piece opposing_piece);
    static Move create_castling(Square move_from, Square move_to, Piece moved_piece);
    static Move create_en_passant(Square move_from, Square move_to, Piece moved_piece);

    [[nodiscard]] Player player() const { return piece.player; }

    bool operator==(const Move& other) const = default;
    bool operator!=(const Move& other) const = default;

private:
    Move(const Square move_from, const Square move_to, const Piece moved_piece, const Piece opposing_piece, const MoveType move_type)
        : from{move_from}, to{move_to}, piece{moved_piece}, captured_piece{opposing_piece}, type{move_type} { }
};

void make_move(Board& board, Move move);
void undo_move(Board& board, Move move);

bool castling_kingside(Square move_to);
bool castling_queenside(Square move_to);

}  // namespace chess
