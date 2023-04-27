#include "list_moves.hpp"

#include "list_moves_detail.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <stdexcept>

namespace chess::detail::list_moves {

const MoveOffset move_left{-1, 0};
const MoveOffset move_right{1, 0};
const MoveOffset move_up{0, -1};
const MoveOffset move_down{0, 1};

int list_moves_for_piece(const Board& board, const BoardPiece board_piece, Moves& moves)
{
    assert(board_piece.piece != no_piece);
    assert(board.piece(board_piece.square) == board_piece.piece);

    switch (board_piece.piece.type) {
        case PieceType::pawn: return list_moves_for_pawn(board, board_piece, moves);
        case PieceType::knight: return list_moves_for_knight(board, board_piece, moves);
        case PieceType::bishop: return list_moves_for_bishop(board, board_piece, moves);
        case PieceType::rook: return list_moves_for_rook(board, board_piece, moves);
        case PieceType::queen: return list_moves_for_queen(board, board_piece, moves);
        case PieceType::king: return list_moves_for_king(board, board_piece, moves);
        default:
            throw std::runtime_error("invalid piece type");
    }
}

int list_moves_for_pawn(const Board& board, const BoardPiece board_piece, Moves& moves)
{
    assert(board_piece.piece.type == PieceType::pawn);
    assert(board.piece(board_piece.square) == board_piece.piece);

    const auto num_previous_moves = moves.size();

    create_pawn_forward_moves(board, board_piece, moves);
    create_pawn_capture_moves(board, board_piece, moves);
    create_pawn_en_passant_moves(board, board_piece, moves);

    return static_cast<int>(moves.size() - num_previous_moves);
}

int list_moves_for_knight(const Board& board, const BoardPiece board_piece, Moves& moves)
{
    assert(board_piece.piece.type == PieceType::knight);
    assert(board.piece(board_piece.square) == board_piece.piece);

    static const std::array<MoveOffset, 8> jumps{
        MoveOffset{-1, -2},
        MoveOffset{1, -2},
        MoveOffset{-2, -1},
        MoveOffset{2, -1},
        MoveOffset{-2, 1},
        MoveOffset{2, 1},
        MoveOffset{-1, 2},
        MoveOffset{1, 2},
    };

    const auto num_previous_moves = moves.size();

    for (const auto& jump : jumps)
        create_knight_move(board, board_piece, moves, jump);

    return static_cast<int>(moves.size() - num_previous_moves);
}

int list_moves_for_bishop(const Board& board, const BoardPiece board_piece, Moves& moves)
{
    assert(board_piece.piece.type == PieceType::bishop);
    assert(board.piece(board_piece.square) == board_piece.piece);

    const auto num_previous_moves = moves.size();

    create_straight_line_moves(board, board_piece, moves, 8, diagonal_move_offset(move_left, move_up));
    create_straight_line_moves(board, board_piece, moves, 8, diagonal_move_offset(move_right, move_up));
    create_straight_line_moves(board, board_piece, moves, 8, diagonal_move_offset(move_left, move_down));
    create_straight_line_moves(board, board_piece, moves, 8, diagonal_move_offset(move_right, move_down));

    return static_cast<int>(moves.size() - num_previous_moves);
}

int list_moves_for_rook(const Board& board, const BoardPiece board_piece, Moves& moves)
{
    assert(board_piece.piece.type == PieceType::rook);
    assert(board.piece(board_piece.square) == board_piece.piece);

    const auto num_previous_moves = moves.size();

    create_straight_line_moves(board, board_piece, moves, 8, move_left);
    create_straight_line_moves(board, board_piece, moves, 8, move_right);
    create_straight_line_moves(board, board_piece, moves, 8, move_up);
    create_straight_line_moves(board, board_piece, moves, 8, move_down);

    return static_cast<int>(moves.size() - num_previous_moves);
}

int list_moves_for_queen(const Board& board, const BoardPiece board_piece, Moves& moves)
{
    assert(board_piece.piece.type == PieceType::queen);
    assert(board.piece(board_piece.square) == board_piece.piece);

    const auto num_previous_moves = moves.size();

    create_straight_line_moves(board, board_piece, moves, 8, move_left);
    create_straight_line_moves(board, board_piece, moves, 8, move_right);
    create_straight_line_moves(board, board_piece, moves, 8, move_up);
    create_straight_line_moves(board, board_piece, moves, 8, move_down);

    create_straight_line_moves(board, board_piece, moves, 8, diagonal_move_offset(move_left, move_up));
    create_straight_line_moves(board, board_piece, moves, 8, diagonal_move_offset(move_right, move_up));
    create_straight_line_moves(board, board_piece, moves, 8, diagonal_move_offset(move_left, move_down));
    create_straight_line_moves(board, board_piece, moves, 8, diagonal_move_offset(move_right, move_down));

    return static_cast<int>(moves.size() - num_previous_moves);
}

int list_moves_for_king(const Board& board, const BoardPiece board_piece, Moves& moves)
{
    assert(board_piece.piece.type == PieceType::king);
    assert(board.piece(board_piece.square) == board_piece.piece);

    const auto num_previous_moves = moves.size();

    create_straight_line_moves(board, board_piece, moves, 1, move_left);
    create_straight_line_moves(board, board_piece, moves, 1, move_right);
    create_straight_line_moves(board, board_piece, moves, 1, move_up);
    create_straight_line_moves(board, board_piece, moves, 1, move_down);

    create_straight_line_moves(board, board_piece, moves, 1, diagonal_move_offset(move_left, move_up));
    create_straight_line_moves(board, board_piece, moves, 1, diagonal_move_offset(move_right, move_up));
    create_straight_line_moves(board, board_piece, moves, 1, diagonal_move_offset(move_left, move_down));
    create_straight_line_moves(board, board_piece, moves, 1, diagonal_move_offset(move_right, move_down));

    create_king_castling_moves(board, board_piece, moves);

    return static_cast<int>(moves.size() - num_previous_moves);
}

int create_straight_line_moves(const Board& board, const BoardPiece board_piece, Moves& moves, const int max_moves, const MoveOffset move_offset)
{
    assert(board.piece(board_piece.square) == board_piece.piece);
    assert(max_moves > 0 && max_moves <= 8);

    const auto num_previous_moves = moves.size();
    Square pos = board_piece.square;

    for (int step = 0; step < max_moves; ++step) {
        pos += move_offset;

        if (!pos.on_board())
            break;

        const auto piece_on_square = board.piece(pos);

        if (piece_on_square == no_piece) {
            moves.push_back(Move{board_piece.square, pos, board_piece.piece, MoveType::normal});
        } else {
            if (piece_on_square.player != board_piece.piece.player)
                moves.push_back(Move{board_piece.square, pos, board_piece.piece, MoveType::capture});

            break;
        }
    }

    return static_cast<int>(moves.size() - num_previous_moves);
}

int create_pawn_forward_moves(const Board& board, const BoardPiece board_piece, Moves& moves)
{
    assert(board_piece.piece.type == PieceType::pawn);
    assert(board.piece(board_piece.square) == board_piece.piece);

    const auto num_previous_moves = moves.size();
    const auto forward_offset = forward_move_offset(board_piece.piece.player);
    const auto opponent_home_rank = nth_rank(board_piece.piece.player, 8);
    const auto max_moves = on_second_rank(board_piece) ? 2 : 1;

    Square pos = board_piece.square;

    for (int step = 0; step < max_moves; ++step) {
        pos += forward_offset;

        if (!pos.on_board())
            break;

        const auto piece_on_square = board.piece(pos);

        if (piece_on_square != no_piece)
            break;

        // promotion if pawn ends on opponents home rank, normal move otherwise
        if (pos.y == opponent_home_rank) {
            for (const auto piece_type : {PieceType::knight, PieceType::rook, PieceType::bishop, PieceType::queen})
                moves.push_back(Move{board_piece.square, pos, Piece{board_piece.piece.player, piece_type}, MoveType::promotion});
        } else {
            moves.push_back(Move{board_piece.square, pos, board_piece.piece, MoveType::normal});
        }
    }

    return static_cast<int>(moves.size() - num_previous_moves);
}

int create_pawn_capture_moves(const Board& board, const BoardPiece board_piece, Moves& moves)
{
    assert(board_piece.piece.type == PieceType::pawn);
    assert(board.piece(board_piece.square) == board_piece.piece);

    const auto num_previous_moves = moves.size();
    const auto forward_offset = forward_move_offset(board_piece.piece.player);
    const auto opponent_home_rank = nth_rank(board_piece.piece.player, 8);

    for (const auto& side_offset : {MoveOffset{-1, forward_offset.y}, MoveOffset{1, forward_offset.y}}) {
        const Square pos = board_piece.square + side_offset;

        if (pos.on_board()) {
            const auto piece_on_square = board.piece(pos);

            if (piece_on_square.player == opposing_player(board_piece.piece.player)) {
                // capture + promotion if pawn ends on opponents home rank, normal capture otherwise
                if (pos.y == opponent_home_rank) {
                    for (const auto piece_type : {PieceType::knight, PieceType::rook, PieceType::bishop, PieceType::queen})
                        moves.push_back(Move{board_piece.square, pos, Piece{board_piece.piece.player, piece_type}, MoveType::capture_and_promotion});
                } else {
                    moves.push_back(Move{board_piece.square, pos, board_piece.piece, MoveType::capture});
                }
            }
        }
    }

    return static_cast<int>(moves.size() - num_previous_moves);
}

int create_pawn_en_passant_moves(const Board& board, const BoardPiece board_piece, Moves& moves)
{
    assert(board_piece.piece.type == PieceType::pawn);
    assert(board.piece(board_piece.square) == board_piece.piece);

    if (board_piece.square.y != nth_rank(board_piece.piece.player, 5))
        return 0;

    const auto num_previous_moves = moves.size();
    const auto forward_offset = forward_move_offset(board_piece.piece.player);

    for (const auto& side_offset : {MoveOffset{-1, 0}, MoveOffset{1, 0}}) {
        const Square opponent_square = board_piece.square + side_offset;

        if (opponent_square.on_board())
            if (board.piece(opponent_square) == Piece{opposing_player(board_piece.piece.player), PieceType::pawn})
                moves.push_back(Move{board_piece.square, board_piece.square + diagonal_move_offset(side_offset, forward_offset), board_piece.piece, MoveType::en_passant});
    }

    return static_cast<int>(moves.size() - num_previous_moves);
}

int create_knight_move(const Board& board, const BoardPiece board_piece, Moves& moves, const MoveOffset jump_offset)
{
    assert(board_piece.piece.type == PieceType::knight);
    assert(board.piece(board_piece.square) == board_piece.piece);
    assert((std::abs(jump_offset.x) == 2 && std::abs(jump_offset.y) == 1) || (std::abs(jump_offset.x) == 1 && std::abs(jump_offset.y) == 2));

    const auto num_previous_moves = moves.size();
    const Square jump_to = board_piece.square + jump_offset;

    if (jump_to.on_board()) {
        const auto piece_on_square = board.piece(jump_to);

        if (piece_on_square == no_piece)
            moves.push_back(Move{board_piece.square, jump_to, board_piece.piece, MoveType::normal});
        else if (piece_on_square.player != board_piece.piece.player)
            moves.push_back(Move{board_piece.square, jump_to, board_piece.piece, MoveType::capture});
    }

    return static_cast<int>(moves.size() - num_previous_moves);
}

int create_king_castling_moves(const Board& board, const BoardPiece board_piece, Moves& moves)
{
    assert(board_piece.piece.type == PieceType::king);
    assert(board.piece(board_piece.square) == board_piece.piece);

    const auto num_previous_moves = moves.size();
    const int first_rank = nth_rank(board_piece.piece.player, 1);

    if (board_piece.square == Square{4, first_rank}) {
        // kingside
        if (board.piece(Square{7, first_rank}) == Piece{board_piece.piece.player, PieceType::rook})
            if (board.empty_square(Square{4 + 1, first_rank}) && board.empty_square(Square{4 + 2, first_rank}))
                moves.push_back(Move{board_piece.square, Square{4 + 2, first_rank}, board_piece.piece, MoveType::castling});

        // queenside
        if (board.piece(Square{0, first_rank}) == Piece{board_piece.piece.player, PieceType::rook})
            if (board.empty_square(Square{4 - 3, first_rank}) && board.empty_square(Square{4 - 2, first_rank}) && board.empty_square(Square{4 - 1, first_rank}))
                moves.push_back(Move{board_piece.square, Square{4 - 2, first_rank}, board_piece.piece, MoveType::castling});
    }

    return static_cast<int>(moves.size() - num_previous_moves);
}

int nth_rank(const Player player, const int nth)
{
    assert(player_is_valid(player));
    assert(nth >= 1 && nth <= 8);

    return (player == Player::white) ? 8 - nth : nth - 1;
}

bool on_second_rank(const BoardPiece board_piece)
{
    assert(player_is_valid(board_piece.piece.player));

    return board_piece.square.y == nth_rank(board_piece.piece.player, 2);
}

int count_moves(const Moves& moves, const MoveType type)
{
    return static_cast<int>(std::count_if(moves.begin(), moves.end(), [=](const Move& move) { return move.type == type; }));
}

MoveOffset forward_move_offset(const Player player)
{
    assert(player_is_valid(player));

    return player == Player::white ? move_up : move_down;
}

MoveOffset diagonal_move_offset(const MoveOffset horizontal_offset, const MoveOffset vertical_offset)
{
    assert(horizontal_offset.x != 0 && horizontal_offset.y == 0);
    assert(vertical_offset.x == 0 && vertical_offset.y != 0);

    return {horizontal_offset.x, vertical_offset.y};
}

}  // namespace chess::detail::list_moves

namespace chess {

using namespace detail::list_moves;

Moves list_moves(const Player player, const Board& board)
{
    Moves moves;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            const Square square{col, row};
            const auto piece = board.piece(square);

            if (piece.player == player)
                list_moves_for_piece(board, BoardPiece{piece, square}, moves);
        }
    }

    return moves;
}

}  // namespace chess
