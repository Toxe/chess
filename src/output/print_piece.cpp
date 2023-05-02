#include "print_piece.hpp"

#include <cassert>
#include <stdexcept>

#include "player_side.hpp"

namespace chess {

char print_piece_letter(const Piece piece)
{
    assert(piece.player != Player::none && piece.type != PieceType::none);

    if (piece.player == Player::white) {
        switch (piece.type) {
            case PieceType::pawn: return 'P';
            case PieceType::knight: return 'N';
            case PieceType::bishop: return 'B';
            case PieceType::rook: return 'R';
            case PieceType::queen: return 'Q';
            case PieceType::king: return 'K';
            default:
                throw std::runtime_error{"invalid piece type"};
        }
    } else {
        switch (piece.type) {
            case PieceType::pawn: return 'p';
            case PieceType::knight: return 'n';
            case PieceType::bishop: return 'b';
            case PieceType::rook: return 'r';
            case PieceType::queen: return 'q';
            case PieceType::king: return 'k';
            default:
                throw std::runtime_error{"invalid piece type"};
        }
    }
}

std::string_view print_piece_symbol(const Piece piece)
{
    assert(piece.player != Player::none && piece.type != PieceType::none);

    if (piece.player == Player::white) {
        switch (piece.type) {
            case PieceType::pawn: return "♟";
            case PieceType::knight: return "♞";
            case PieceType::bishop: return "♝";
            case PieceType::rook: return "♜";
            case PieceType::queen: return "♛";
            case PieceType::king: return "♚";
            default:
                throw std::runtime_error{"invalid piece type"};
        }
    } else {
        switch (piece.type) {
            case PieceType::pawn: return "♙";
            case PieceType::knight: return "♘";
            case PieceType::bishop: return "♗";
            case PieceType::rook: return "♖";
            case PieceType::queen: return "♕";
            case PieceType::king: return "♔";
            default:
                throw std::runtime_error{"invalid piece type"};
        }
    }
}

std::string_view print_piece_type(const PieceType type)
{
    assert(type != PieceType::none);

    switch (type) {
        case PieceType::pawn: return "pawn";
        case PieceType::knight: return "knight";
        case PieceType::bishop: return "bishop";
        case PieceType::rook: return "rook";
        case PieceType::queen: return "queen";
        case PieceType::king: return "king";
        default:
            throw std::runtime_error{"invalid piece type"};
    }
}

std::string print_piece_descriptive(const Piece piece)
{
    assert(piece.player != Player::none && piece.type != PieceType::none);

    return std::string{print_player(piece.player)} + " " + std::string{print_piece_type(piece.type)};
}

}  // namespace chess
