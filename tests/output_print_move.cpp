#include "catch2/catch_test_macros.hpp"

#include "../src/output/print_move.hpp"

namespace chess {

TEST_CASE("output/print_move")
{
    SECTION("print_move()")
    {
        CHECK(print_move(Move::create_normal(Square{"a2"}, Square{"a4"}, Piece{'P'})) == "a2a4 (white pawn a2 to a4)");
        CHECK(print_move(Move::create_promotion(Square{"g2"}, Square{"g1"}, Piece{'q'})) == "g2g1 (black pawn g2 to g1, promotion to queen)");
        CHECK(print_move(Move::create_capture(Square{"h1"}, Square{"h8"}, Piece{'R'}, Piece{'r'})) == "h1h8 (white rook h1 to h8, capture black rook)");
        CHECK(print_move(Move::create_capture_and_promotion(Square{"g7"}, Square{"h8"}, Piece{'Q'}, Piece{'r'})) == "g7h8 (white pawn g7 to h8, capture black rook, promotion to queen)");
        CHECK(print_move(Move::create_castling(Square{"e1"}, Square{"g1"}, Piece{'K'})) == "e1g1 (white king e1 castling kingside to g1)");
        CHECK(print_move(Move::create_castling(Square{"e1"}, Square{"c1"}, Piece{'K'})) == "e1c1 (white king e1 castling queenside to c1)");
        CHECK(print_move(Move::create_en_passant(Square{"a4"}, Square{"b3"}, Piece{'p'})) == "a4b3 (black pawn a4 en passant to b3)");
    }
}

}  // namespace chess
