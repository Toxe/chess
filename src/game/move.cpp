#include "move.hpp"

#include <cassert>
#include <cmath>

#include "../board/rank.hpp"

namespace chess {

Move Move::create_normal(const Square move_from, const Square move_to, const Piece moved_piece)
{
    return Move{move_from, move_to, moved_piece, no_piece, MoveType::normal};
}

Move Move::create_promotion(const Square move_from, const Square move_to, const Piece promoted_piece)
{
    assert(promoted_piece.type == PieceType::queen || promoted_piece.type == PieceType::knight || promoted_piece.type == PieceType::bishop || promoted_piece.type == PieceType::rook);
    assert(nth_rank(promoted_piece.player, 7) == move_from.y && nth_rank(promoted_piece.player, 8) == move_to.y);
    assert(move_from.x == move_to.x);

    return Move{move_from, move_to, promoted_piece, no_piece, MoveType::promotion};
}

Move Move::create_capture(const Square move_from, const Square move_to, const Piece moved_piece, const Piece opposing_piece)
{
    assert(opposing_player(moved_piece.player) == opposing_piece.player);

    return Move{move_from, move_to, moved_piece, opposing_piece, MoveType::capture};
}

Move Move::create_capture_and_promotion(const Square move_from, const Square move_to, const Piece promoted_piece, const Piece opposing_piece)
{
    assert(promoted_piece.type == PieceType::queen || promoted_piece.type == PieceType::knight || promoted_piece.type == PieceType::bishop || promoted_piece.type == PieceType::rook);
    assert(opposing_player(promoted_piece.player) == opposing_piece.player);
    assert(nth_rank(promoted_piece.player, 7) == move_from.y && nth_rank(promoted_piece.player, 8) == move_to.y);
    assert(std::abs(move_to.x - move_from.x) == 1);

    return Move{move_from, move_to, promoted_piece, opposing_piece, MoveType::capture_and_promotion};
}

Move Move::create_castling(const Square move_from, const Square move_to, const Piece moved_piece)
{
    assert(moved_piece.type == PieceType::king);
    assert(on_home_rank(moved_piece.player, move_from) && on_home_rank(moved_piece.player, move_to));
    assert((castling_kingside(move_to) && move_from.x == 4 && move_to.x == 6) || (castling_queenside(move_to) && move_from.x == 4 && move_to.x == 2));

    return Move{move_from, move_to, moved_piece, no_piece, MoveType::castling};
}

Move Move::create_en_passant(const Square move_from, const Square move_to, const Piece moved_piece)
{
    assert(moved_piece.type == PieceType::pawn);
    assert(nth_rank(moved_piece.player, 5) == move_from.y && nth_rank(moved_piece.player, 6) == move_to.y);
    assert(std::abs(move_to.x - move_from.x) == 1);

    return Move{move_from, move_to, moved_piece, Piece{opposing_player(moved_piece.player), PieceType::pawn}, MoveType::en_passant};
}

void make_move(Board& board, const Move move)
{
    assert(move.from.on_board());
    assert(move.to.on_board());

    switch (move.type) {
        case MoveType::normal:
            assert(board.piece(move.from) == move.piece);
            assert(board.piece(move.to) == no_piece);
            board.change_piece(move.from, no_piece);
            board.change_piece(move.to, move.piece);
            break;

        case MoveType::promotion:
            assert((board.piece(move.from) == Piece{move.piece.player, PieceType::pawn}));
            assert(board.piece(move.to) == no_piece);
            board.change_piece(move.from, no_piece);
            board.change_piece(move.to, move.piece);
            break;

        case MoveType::capture:
            assert(board.piece(move.from) == move.piece);
            assert(board.piece(move.to) == move.captured_piece);
            board.change_piece(move.from, no_piece);
            board.change_piece(move.to, move.piece);
            break;

        case MoveType::capture_and_promotion:
            assert((board.piece(move.from) == Piece{move.piece.player, PieceType::pawn}));
            assert(board.piece(move.to) == move.captured_piece);
            board.change_piece(move.from, no_piece);
            board.change_piece(move.to, move.piece);
            break;

        case MoveType::castling:
            assert(board.piece(move.from) == move.piece);
            assert(board.piece(move.to) == no_piece);
            board.change_piece(move.from, no_piece);
            board.change_piece(move.to, move.piece);

            // kingside or queenside?
            if (castling_kingside(move.to)) {
                assert(board.piece(Square{static_cast<Square::coordinates_type>(5), move.to.y}) == no_piece);
                assert((board.piece(Square{static_cast<Square::coordinates_type>(7), move.to.y}) == Piece{move.piece.player, PieceType::rook}));
                board.change_piece(Square{static_cast<Square::coordinates_type>(5), move.to.y}, Piece{move.piece.player, PieceType::rook});
                board.change_piece(Square{static_cast<Square::coordinates_type>(7), move.to.y}, no_piece);
            } else {
                assert(board.piece(Square{static_cast<Square::coordinates_type>(3), move.to.y}) == no_piece);
                assert((board.piece(Square{static_cast<Square::coordinates_type>(0), move.to.y}) == Piece{move.piece.player, PieceType::rook}));
                board.change_piece(Square{static_cast<Square::coordinates_type>(3), move.to.y}, Piece{move.piece.player, PieceType::rook});
                board.change_piece(Square{static_cast<Square::coordinates_type>(0), move.to.y}, no_piece);
            }
            break;

        case MoveType::en_passant:
            assert(board.piece(move.from) == move.piece);
            assert(board.piece(move.to) == no_piece);
            assert(board.piece(Square{move.to.x, move.from.y}) == move.captured_piece);
            board.change_piece(move.from, no_piece);
            board.change_piece(move.to, move.piece);
            board.change_piece(Square{move.to.x, move.from.y}, no_piece);
            break;
    }
}

void undo_move(Board& board, const Move move)
{
    assert(move.from.on_board());
    assert(move.to.on_board());

    switch (move.type) {
        case MoveType::normal:
            assert(board.piece(move.from) == no_piece);
            assert(board.piece(move.to) == move.piece);
            board.change_piece(move.from, move.piece);
            board.change_piece(move.to, no_piece);
            break;

        case MoveType::promotion:
            assert(board.piece(move.from) == no_piece);
            assert(board.piece(move.to) == move.piece);
            board.change_piece(move.from, Piece{move.piece.player, PieceType::pawn});
            board.change_piece(move.to, no_piece);
            break;

        case MoveType::capture:
            assert(board.piece(move.from) == no_piece);
            assert(board.piece(move.to) == move.piece);
            board.change_piece(move.from, move.piece);
            board.change_piece(move.to, move.captured_piece);
            break;

        case MoveType::capture_and_promotion:
            assert(board.piece(move.from) == no_piece);
            assert(board.piece(move.to) == move.piece);
            board.change_piece(move.from, Piece{move.piece.player, PieceType::pawn});
            board.change_piece(move.to, move.captured_piece);
            break;

        case MoveType::castling:
            assert(board.piece(move.from) == no_piece);
            assert(board.piece(move.to) == move.piece);
            board.change_piece(move.from, move.piece);
            board.change_piece(move.to, no_piece);

            // kingside or queenside?
            if (castling_kingside(move.to)) {
                assert((board.piece(Square{static_cast<Square::coordinates_type>(5), move.to.y}) == Piece{move.piece.player, PieceType::rook}));
                assert(board.piece(Square{static_cast<Square::coordinates_type>(7), move.to.y}) == no_piece);
                board.change_piece(Square{static_cast<Square::coordinates_type>(5), move.to.y}, no_piece);
                board.change_piece(Square{static_cast<Square::coordinates_type>(7), move.to.y}, Piece{move.piece.player, PieceType::rook});
            } else {
                assert((board.piece(Square{static_cast<Square::coordinates_type>(3), move.to.y}) == Piece{move.piece.player, PieceType::rook}));
                assert(board.piece(Square{static_cast<Square::coordinates_type>(0), move.to.y}) == no_piece);
                board.change_piece(Square{static_cast<Square::coordinates_type>(3), move.to.y}, no_piece);
                board.change_piece(Square{static_cast<Square::coordinates_type>(0), move.to.y}, Piece{move.piece.player, PieceType::rook});
            }
            break;

        case MoveType::en_passant:
            assert(board.piece(move.from) == no_piece);
            assert(board.piece(move.to) == move.piece);
            assert(board.piece(Square{move.to.x, move.from.y}) == no_piece);
            board.change_piece(move.from, move.piece);
            board.change_piece(move.to, no_piece);
            board.change_piece(Square{move.to.x, move.from.y}, move.captured_piece);
            break;
    }
}

bool castling_kingside(const Square move_to)
{
    return move_to.x == 6;
}

bool castling_queenside(const Square move_to)
{
    return move_to.x == 2;
}

}  // namespace chess
