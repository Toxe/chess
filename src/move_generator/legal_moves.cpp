#include "legal_moves.hpp"

#include <algorithm>
#include <cassert>

#include "list_moves.hpp"

namespace chess {

bool can_castle(Board& board, const GameState game_state, const Move move)
{
    assert(move.type == MoveType::castling);

    if (is_check(board, move.piece.player))
        return false;

    const bool kingside = castling_kingside(move.to);

    if (move.piece.player == Player::white) {
        if (!game_state.castling_ability.has(kingside ? CastlingRight::white_king : CastlingRight::white_queen))
            return false;
    } else {
        if (!game_state.castling_ability.has(kingside ? CastlingRight::black_king : CastlingRight::black_queen))
            return false;
    }

    const Square square_under_attack{kingside ? static_cast<Square::coordinates_type>(5) : static_cast<Square::coordinates_type>(3), move.to.y};

    make_move(board, move);

    if (is_square_under_attack(board, move.piece.player, square_under_attack)) {
        undo_move(board, move);
        return false;
    }

    undo_move(board, move);

    return true;
}

bool can_en_passant(const GameState game_state, const Move move)
{
    assert(move.type == MoveType::en_passant);

    if (!game_state.en_passant_target_square)
        return false;

    return move.to == *game_state.en_passant_target_square;
}

bool is_legal_move(Board& board, const GameState game_state, const Move move)
{
    // en passant
    if (move.type == MoveType::en_passant)
        if (!can_en_passant(game_state, move))
            return false;

    // castling
    if (move.type == MoveType::castling)
        if (!can_castle(board, game_state, move))
            return false;

    // check
    make_move(board, move);

    if (is_check(board, move.piece.player)) {
        undo_move(board, move);
        return false;
    }

    undo_move(board, move);

    return true;
}

bool is_check(const Board& board, const Player player)
{
    const Player opponent = opposing_player(player);
    const auto moves = list_moves(board, opponent);
    const auto king = Piece{player, PieceType::king};

    return std::any_of(moves.begin(), moves.end(), [=](const Move& move) { return move.captured_piece == king; });
}

bool is_square_under_attack(const Board& board, const Player player, const Square square_under_attack)
{
    const Player opponent = opposing_player(player);
    const auto moves = list_moves(board, opponent);

    return std::any_of(moves.begin(), moves.end(), [=](const Move& move) { return move.to == square_under_attack; });
}

}  // namespace chess
