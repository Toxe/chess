#include "print_move.hpp"

#include <stdexcept>

#include "fmt/core.h"

#include "print_piece.hpp"
#include "print_square.hpp"

namespace chess {

std::string detailed_description(const Move move)
{
    switch (move.type) {
        case MoveType::normal:
            return fmt::format("{} {} to {}", print_piece_descriptive(move.piece), print_square(move.from), print_square(move.to));
            break;
        case MoveType::promotion:
            return fmt::format("{} {} to {}, promotion to {}", print_piece_descriptive(Piece{move.piece.player, PieceType::pawn}), print_square(move.from), print_square(move.to), print_piece_type(move.piece.type));
            break;
        case MoveType::capture:
            return fmt::format("{} {} to {}, capture {}", print_piece_descriptive(move.piece), print_square(move.from), print_square(move.to), print_piece_descriptive(move.captured_piece));
            break;
        case MoveType::capture_and_promotion:
            return fmt::format("{} {} to {}, capture {}, promotion to {}", print_piece_descriptive(Piece{move.piece.player, PieceType::pawn}), print_square(move.from), print_square(move.to), print_piece_descriptive(move.captured_piece), print_piece_type(move.piece.type));
            break;
        case MoveType::castling:
            return fmt::format("{} {} castling {} to {}", print_piece_descriptive(move.piece), print_square(move.from), castling_kingside(move.to) ? "kingside" : "queenside", print_square(move.to));
            break;
        case MoveType::en_passant:
            return fmt::format("{} {} en passant to {}", print_piece_descriptive(move.piece), print_square(move.from), print_square(move.to));
            break;
        default:
            throw std::runtime_error{"invalid move type"};
    }
}

std::string print_move(const Move move)
{
    return fmt::format("{}{} ({})", print_square(move.from), print_square(move.to), detailed_description(move));
}

}  // namespace chess
