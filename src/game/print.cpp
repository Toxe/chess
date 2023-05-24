#include "print.hpp"

#include <cassert>
#include <stdexcept>
#include <utility>

#include "fmt/core.h"

#include "../board/print.hpp"

namespace chess {

// ======== Player ==================================================

std::string_view print_player(const Player player)
{
    assert(player_is_valid(player));

    return player == Player::white ? "white" : "black";
}

std::string_view print_player_side(const Player player)
{
    assert(player_is_valid(player));

    return player == Player::white ? "White" : "Black";
}

// ======== PieceType ===============================================

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
        case PieceType::none: throw std::runtime_error{"invalid piece type"};
    }

    std::unreachable();
}

// ======== Piece ===================================================

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
            case PieceType::none: throw std::runtime_error{"invalid piece type"};
        }
    } else {
        switch (piece.type) {
            case PieceType::pawn: return 'p';
            case PieceType::knight: return 'n';
            case PieceType::bishop: return 'b';
            case PieceType::rook: return 'r';
            case PieceType::queen: return 'q';
            case PieceType::king: return 'k';
            case PieceType::none: throw std::runtime_error{"invalid piece type"};
        }
    }

    std::unreachable();
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
            case PieceType::none: throw std::runtime_error{"invalid piece type"};
        }
    } else {
        switch (piece.type) {
            case PieceType::pawn: return "♙";
            case PieceType::knight: return "♘";
            case PieceType::bishop: return "♗";
            case PieceType::rook: return "♖";
            case PieceType::queen: return "♕";
            case PieceType::king: return "♔";
            case PieceType::none: throw std::runtime_error{"invalid piece type"};
        }
    }

    std::unreachable();
}

std::string print_piece_descriptive(const Piece piece)
{
    assert(piece.player != Player::none && piece.type != PieceType::none);

    return std::string{print_player(piece.player)} + " " + std::string{print_piece_type(piece.type)};
}

// ======== Move ====================================================

std::string detailed_move_description(const Move move)
{
    switch (move.type) {
        case MoveType::normal: return fmt::format("{} {} to {}", print_piece_descriptive(move.piece), print_square(move.from), print_square(move.to));
        case MoveType::promotion: return fmt::format("{} {} to {}, promotion to {}", print_piece_descriptive(Piece{move.player(), PieceType::pawn}), print_square(move.from), print_square(move.to), print_piece_type(move.piece.type));
        case MoveType::capture: return fmt::format("{} {} to {}, capture {}", print_piece_descriptive(move.piece), print_square(move.from), print_square(move.to), print_piece_descriptive(move.captured_piece));
        case MoveType::capture_and_promotion: return fmt::format("{} {} to {}, capture {}, promotion to {}", print_piece_descriptive(Piece{move.player(), PieceType::pawn}), print_square(move.from), print_square(move.to), print_piece_descriptive(move.captured_piece), print_piece_type(move.piece.type));
        case MoveType::castling: return fmt::format("{} {} castling {} to {}", print_piece_descriptive(move.piece), print_square(move.from), castling_kingside(move.to) ? "kingside" : "queenside", print_square(move.to));
        case MoveType::en_passant: return fmt::format("{} {} en passant to {}", print_piece_descriptive(move.piece), print_square(move.from), print_square(move.to));
    }

    std::unreachable();
}

std::string print_move(const Move move)
{
    return fmt::format("{}{} ({})", print_square(move.from), print_square(move.to), detailed_move_description(move));
}

// ======== WinCondition ============================================

std::string generate_ongoing_game_output()
{
    return "The game is not over yet.";
}

std::string generate_checkmate_output(const Player player)
{
    return fmt::format("Checkmate {}! {} won!", print_player_side(player), print_player_side(opposing_player(player)));
}

std::string generate_stalemate_output()
{
    return "Stalemate!";
}

std::string print_game_over(const WinCondition win_condition)
{
    switch (win_condition) {
        case WinCondition::none: return generate_ongoing_game_output();
        case WinCondition::checkmate_white: return generate_checkmate_output(Player::white);
        case WinCondition::checkmate_black: return generate_checkmate_output(Player::black);
        case WinCondition::stalemate: return generate_stalemate_output();
    }

    std::unreachable();
}

}  // namespace chess
