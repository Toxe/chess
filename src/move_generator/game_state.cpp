#include "game_state.hpp"

#include <cmath>

#include "../board/rank.hpp"

namespace chess {

GameState update_game_state(GameState game_state, const Move move)
{
    // halfmove clock
    if (move.piece.type == PieceType::pawn || move.type == MoveType::capture || move.type == MoveType::capture_and_promotion || move.type == MoveType::en_passant)
        game_state.halfmove_clock = 0;
    else
        ++game_state.halfmove_clock;

    // fullmove counter
    if (move.player() == Player::black)
        ++game_state.fullmove_counter;

    // castling ability
    if (move.piece.type == PieceType::king) {
        if (move.player() == Player::white) {
            game_state.castling_ability.clear(CastlingRight::white_king);
            game_state.castling_ability.clear(CastlingRight::white_queen);
        } else {
            game_state.castling_ability.clear(CastlingRight::black_king);
            game_state.castling_ability.clear(CastlingRight::black_queen);
        }
    }

    if (move.piece.type == PieceType::rook) {
        if (move.player() == Player::white) {
            if (move.from == Square{"a1"})
                game_state.castling_ability.clear(CastlingRight::white_queen);
            else if (move.from == Square{"h1"})
                game_state.castling_ability.clear(CastlingRight::white_king);
        } else {
            if (move.from == Square{"a8"})
                game_state.castling_ability.clear(CastlingRight::black_queen);
            else if (move.from == Square{"h8"})
                game_state.castling_ability.clear(CastlingRight::black_king);
        }
    }

    if (move.captured_piece.type == PieceType::rook) {
        if (move.captured_piece.player == Player::white) {
            if (move.to == Square{"a1"})
                game_state.castling_ability.clear(CastlingRight::white_queen);
            else if (move.to == Square{"h1"})
                game_state.castling_ability.clear(CastlingRight::white_king);
        } else {
            if (move.to == Square{"a8"})
                game_state.castling_ability.clear(CastlingRight::black_queen);
            else if (move.to == Square{"h8"})
                game_state.castling_ability.clear(CastlingRight::black_king);
        }
    }

    // en passant target square
    game_state.en_passant_target_square = std::nullopt;

    if (move.piece.type == PieceType::pawn)
        if (on_second_rank(move.player(), move.from))  // from 2nd...
            if (move.to.y == nth_rank(move.player(), 4))  // ...to 4th rank?
                game_state.en_passant_target_square = Square{move.from.x, static_cast<Square::coordinates_type>(nth_rank(move.player(), 3))};

    return game_state;
}

}  // namespace chess
