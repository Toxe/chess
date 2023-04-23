#include "catch2/catch_test_macros.hpp"

#include "../src/output/print_move.hpp"

namespace chess {

TEST_CASE("output/print_move")
{
    SECTION("print_move()")
    {
        CHECK(print_move(Move{Square{"d4"}, Square{"g4"}, Piece{Player::black, PieceType::rook}}) == "d4g4");
        CHECK(print_move(Move{Square{"b2"}, Square{"b4"}, Piece{Player::white, PieceType::pawn}}) == "b2b4");
    }
}

}  // namespace chess
