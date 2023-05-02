#include "catch2/catch_test_macros.hpp"

#include "../src/move_generator/moves.hpp"

namespace chess {

TEST_CASE("move_generator/moves")
{
    SECTION("count_moves()")
    {
        Moves moves{
            Move::create_normal(Square{"d2"}, Square{"d4"}, Piece{'P'}),
            Move::create_normal(Square{"e2"}, Square{"e4"}, Piece{'P'}),
            Move::create_normal(Square{"f2"}, Square{"f3"}, Piece{'P'}),
            Move::create_promotion(Square{"g7"}, Square{"g8"}, Piece{'Q'}),
            Move::create_capture(Square{"h1"}, Square{"h8"}, Piece{'R'}, Piece{'r'}),
            Move::create_capture(Square{"h8"}, Square{"h1"}, Piece{'r'}, Piece{'R'}),
            Move::create_capture_and_promotion(Square{"g7"}, Square{"h8"}, Piece{'Q'}, Piece{'r'}),
            Move::create_castling(Square{"e1"}, Square{"g1"}, Piece{'K'}),
            Move::create_castling(Square{"e8"}, Square{"c8"}, Piece{'k'}),
            Move::create_en_passant(Square{"d5"}, Square{"e6"}, Piece{'P'}),
        };

        CHECK(count_moves(moves, MoveType::normal) == 3);
        CHECK(count_moves(moves, MoveType::promotion) == 1);
        CHECK(count_moves(moves, MoveType::capture) == 2);
        CHECK(count_moves(moves, MoveType::capture_and_promotion) == 1);
        CHECK(count_moves(moves, MoveType::castling) == 2);
        CHECK(count_moves(moves, MoveType::en_passant) == 1);

        CHECK(count_moves({}, MoveType::normal) == 0);
    }
}

}  // namespace chess
