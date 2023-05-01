#pragma once

#include "../board/board.hpp"
#include "moves.hpp"

namespace chess::detail::list_moves {

struct BoardPiece {
    Piece piece;
    Square square;
};

using MoveOffset = Coords<char>;

int list_moves_for_piece(const Board& board, BoardPiece board_piece, Moves& moves);
int list_moves_for_pawn(const Board& board, BoardPiece board_piece, Moves& moves);
int list_moves_for_knight(const Board& board, BoardPiece board_piece, Moves& moves);
int list_moves_for_bishop(const Board& board, BoardPiece board_piece, Moves& moves);
int list_moves_for_rook(const Board& board, BoardPiece board_piece, Moves& moves);
int list_moves_for_queen(const Board& board, BoardPiece board_piece, Moves& moves);
int list_moves_for_king(const Board& board, BoardPiece board_piece, Moves& moves);

int create_straight_line_moves(const Board& board, BoardPiece board_piece, Moves& moves, int max_moves, MoveOffset move_offset);
int create_pawn_forward_moves(const Board& board, BoardPiece board_piece, Moves& moves);
int create_pawn_capture_moves(const Board& board, BoardPiece board_piece, Moves& moves);
int create_pawn_en_passant_moves(const Board& board, BoardPiece board_piece, Moves& moves);
int create_knight_move(const Board& board, BoardPiece board_piece, Moves& moves, MoveOffset jump_offset);
int create_king_castling_moves(const Board& board, BoardPiece board_piece, Moves& moves);

MoveOffset forward_move_offset(Player player);
MoveOffset diagonal_move_offset(MoveOffset horizontal_offset, MoveOffset vertical_offset);

}  // namespace chess::detail::list_moves
