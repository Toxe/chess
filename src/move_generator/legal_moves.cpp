#include "legal_moves.hpp"

#include <algorithm>
#include <cassert>

#include "../board/file.hpp"
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

MoveLegality can_castle(Board& board, const GameState game_state, const Move move)
{
    assert(move.type == MoveType::castling);

    if (is_check(board, move.player()))
        return MoveLegality::check;

    const bool kingside = castling_kingside(move.to);

    if (move.player() == Player::white) {
        if (!game_state.castling_ability.has(kingside ? CastlingRight::white_king : CastlingRight::white_queen))
            return MoveLegality::no_castling_ability;
    } else {
        if (!game_state.castling_ability.has(kingside ? CastlingRight::black_king : CastlingRight::black_queen))
            return MoveLegality::no_castling_ability;
    }

    const Square square_under_attack{from_file(kingside ? 'f' : 'd'), move.to.y};

    if (would_square_be_under_attack(board, move, square_under_attack))
        return MoveLegality::square_under_attack;

    return MoveLegality::ok;
}

MoveLegality can_en_passant(const GameState game_state, const Move move)
{
    assert(move.type == MoveType::en_passant);

    if (!game_state.en_passant_target_square)
        return MoveLegality::en_passant_target_square_not_set;

    return (move.to == *game_state.en_passant_target_square) ? MoveLegality::ok : MoveLegality::en_passant_target_square_wrong;
}

MoveLegality check_legal_move(Board& board, const GameState game_state, const Move move)
{
    // en passant
    if (move.type == MoveType::en_passant)
        if (const auto legal = can_en_passant(game_state, move); legal != MoveLegality::ok)
            return legal;

    // castling
    if (move.type == MoveType::castling)
        if (const auto legal = can_castle(board, game_state, move); legal != MoveLegality::ok)
            return legal;

    // check
    if (move_would_result_in_check(board, move))
        return MoveLegality::would_result_in_check;

    return MoveLegality::ok;
}

}  // namespace chess
