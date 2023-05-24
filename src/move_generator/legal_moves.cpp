#include "legal_moves.hpp"

#include <algorithm>
#include <cassert>

#include "list_moves.hpp"

namespace chess {

bool is_check(const Board& board, const Player player)
{
    const Player opponent = opposing_player(player);
    const auto opponent_moves = list_moves(board, opponent);
    const auto king = Piece{player, PieceType::king};

    return std::any_of(opponent_moves.begin(), opponent_moves.end(), [=](const Move& move) { return move.captured_piece == king; });
}

bool move_would_result_in_check(Board& board, const Move move)
{
    make_move(board, move);
    const bool check = is_check(board, move.player());
    undo_move(board, move);

    return check;
}

bool would_square_be_under_attack(Board& board, const Move move, const Square square_under_attack)
{
    const Player opponent = opposing_player(move.player());

    make_move(board, move);
    const auto opponent_moves = list_moves(board, opponent);
    undo_move(board, move);

    return std::any_of(opponent_moves.begin(), opponent_moves.end(), [=](const Move& m) { return m.to == square_under_attack; });
}

bool can_castle(Board& board, const GameState game_state, const Move move)
{
    assert(move.type == MoveType::castling);

    if (is_check(board, move.player()))
        return false;

    const bool kingside = castling_kingside(move.to);

    if (move.player() == Player::white) {
        if (!game_state.castling_ability.has(kingside ? CastlingRight::white_king : CastlingRight::white_queen))
            return false;
    } else {
        if (!game_state.castling_ability.has(kingside ? CastlingRight::black_king : CastlingRight::black_queen))
            return false;
    }

    const Square square_under_attack{kingside ? static_cast<Square::coordinates_type>(5) : static_cast<Square::coordinates_type>(3), move.to.y};

    if (would_square_be_under_attack(board, move, square_under_attack))
        return false;

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
    if (move_would_result_in_check(board, move))
        return false;

    return true;
}

}  // namespace chess
