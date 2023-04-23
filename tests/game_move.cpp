#include "catch2/catch_test_macros.hpp"

#include "../src/game/move.hpp"

namespace chess {

TEST_CASE("game/move")
{
    SECTION("construct")
    {
        const Move move{Square{"d4"}, Square{"g4"}, Piece{Player::black, PieceType::rook}};

        CHECK(move.from == Square{"d4"});
        CHECK(move.to == Square{"g4"});
        CHECK(move.piece.player == Player::black);
        CHECK(move.piece.type == PieceType::rook);
    }
}

}  // namespace chess
