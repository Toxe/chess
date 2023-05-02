#include "catch2/catch_test_macros.hpp"

#include "../src/output/print_piece.hpp"

namespace chess {

TEST_CASE("output/print_piece")
{
    SECTION("print_piece_letter()")
    {
        CHECK(print_piece_letter(Piece{'p'}) == 'p');
        CHECK(print_piece_letter(Piece{'n'}) == 'n');
        CHECK(print_piece_letter(Piece{'b'}) == 'b');
        CHECK(print_piece_letter(Piece{'r'}) == 'r');
        CHECK(print_piece_letter(Piece{'q'}) == 'q');
        CHECK(print_piece_letter(Piece{'k'}) == 'k');

        CHECK(print_piece_letter(Piece{'P'}) == 'P');
        CHECK(print_piece_letter(Piece{'N'}) == 'N');
        CHECK(print_piece_letter(Piece{'B'}) == 'B');
        CHECK(print_piece_letter(Piece{'R'}) == 'R');
        CHECK(print_piece_letter(Piece{'Q'}) == 'Q');
        CHECK(print_piece_letter(Piece{'K'}) == 'K');
    }

    SECTION("print_piece_symbol()")
    {
        CHECK(print_piece_symbol(Piece{'p'}) == "♙");
        CHECK(print_piece_symbol(Piece{'n'}) == "♘");
        CHECK(print_piece_symbol(Piece{'b'}) == "♗");
        CHECK(print_piece_symbol(Piece{'r'}) == "♖");
        CHECK(print_piece_symbol(Piece{'q'}) == "♕");
        CHECK(print_piece_symbol(Piece{'k'}) == "♔");

        CHECK(print_piece_symbol(Piece{'P'}) == "♟");
        CHECK(print_piece_symbol(Piece{'N'}) == "♞");
        CHECK(print_piece_symbol(Piece{'B'}) == "♝");
        CHECK(print_piece_symbol(Piece{'R'}) == "♜");
        CHECK(print_piece_symbol(Piece{'Q'}) == "♛");
        CHECK(print_piece_symbol(Piece{'K'}) == "♚");
    }

    SECTION("print_piece_descriptive()")
    {
        CHECK(print_piece_descriptive(Piece{'p'}) == "black pawn");
        CHECK(print_piece_descriptive(Piece{'n'}) == "black knight");
        CHECK(print_piece_descriptive(Piece{'b'}) == "black bishop");
        CHECK(print_piece_descriptive(Piece{'r'}) == "black rook");
        CHECK(print_piece_descriptive(Piece{'q'}) == "black queen");
        CHECK(print_piece_descriptive(Piece{'k'}) == "black king");

        CHECK(print_piece_descriptive(Piece{'P'}) == "white pawn");
        CHECK(print_piece_descriptive(Piece{'N'}) == "white knight");
        CHECK(print_piece_descriptive(Piece{'B'}) == "white bishop");
        CHECK(print_piece_descriptive(Piece{'R'}) == "white rook");
        CHECK(print_piece_descriptive(Piece{'Q'}) == "white queen");
        CHECK(print_piece_descriptive(Piece{'K'}) == "white king");
    }
}

}  // namespace chess
