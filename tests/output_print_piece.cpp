#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

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
        CHECK_THAT(print_piece_symbol(Piece{'p'}), Catch::Matchers::Equals("♙"));
        CHECK_THAT(print_piece_symbol(Piece{'n'}), Catch::Matchers::Equals("♘"));
        CHECK_THAT(print_piece_symbol(Piece{'b'}), Catch::Matchers::Equals("♗"));
        CHECK_THAT(print_piece_symbol(Piece{'r'}), Catch::Matchers::Equals("♖"));
        CHECK_THAT(print_piece_symbol(Piece{'q'}), Catch::Matchers::Equals("♕"));
        CHECK_THAT(print_piece_symbol(Piece{'k'}), Catch::Matchers::Equals("♔"));

        CHECK_THAT(print_piece_symbol(Piece{'P'}), Catch::Matchers::Equals("♟"));
        CHECK_THAT(print_piece_symbol(Piece{'N'}), Catch::Matchers::Equals("♞"));
        CHECK_THAT(print_piece_symbol(Piece{'B'}), Catch::Matchers::Equals("♝"));
        CHECK_THAT(print_piece_symbol(Piece{'R'}), Catch::Matchers::Equals("♜"));
        CHECK_THAT(print_piece_symbol(Piece{'Q'}), Catch::Matchers::Equals("♛"));
        CHECK_THAT(print_piece_symbol(Piece{'K'}), Catch::Matchers::Equals("♚"));
    }
}

}  // namespace chess
