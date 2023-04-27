#include "catch2/catch_test_macros.hpp"

#include "../src/game/move.hpp"

namespace chess {

TEST_CASE("game/move")
{
    SECTION("construct")
    {
        const Move move{Square{"d4"}, Square{"g4"}, Piece{Player::black, PieceType::rook}, MoveType::capture};

        CHECK(move.from == Square{"d4"});
        CHECK(move.to == Square{"g4"});
        CHECK(move.piece.player == Player::black);
        CHECK(move.piece.type == PieceType::rook);
        CHECK(move.type == MoveType::capture);
    }

    SECTION("comparison")
    {
        const Move move{Square{"d2"}, Square{"d4"}, Piece{'P'}, MoveType::normal};

        CHECK(move == move);
        CHECK(move != Move{Square{"d2"}, Square{"d4"}, Piece{'P'}, MoveType::capture});
        CHECK(move != Move{Square{"d2"}, Square{"d4"}, Piece{'N'}, MoveType::normal});
        CHECK(move != Move{Square{"d2"}, Square{"d3"}, Piece{'P'}, MoveType::normal});
        CHECK(move != Move{Square{"d3"}, Square{"d4"}, Piece{'P'}, MoveType::normal});

        CHECK((move != move) == false);
        CHECK((move == Move{Square{"d2"}, Square{"d4"}, Piece{'P'}, MoveType::capture}) == false);
        CHECK((move == Move{Square{"d2"}, Square{"d4"}, Piece{'N'}, MoveType::normal}) == false);
        CHECK((move == Move{Square{"d2"}, Square{"d3"}, Piece{'P'}, MoveType::normal}) == false);
        CHECK((move == Move{Square{"d3"}, Square{"d4"}, Piece{'P'}, MoveType::normal}) == false);
    }
}

}  // namespace chess
