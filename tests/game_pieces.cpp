#include "catch2/catch_test_macros.hpp"

#include "../src/game/pieces.hpp"

namespace chess {

TEST_CASE("game/pieces")
{
    SECTION("can construct pieces with Player and PieceType")
    {
        for (const auto player : {Player::none, Player::white, Player::black}) {
            for (const auto type : {PieceType::none, PieceType::pawn, PieceType::knight, PieceType::bishop, PieceType::rook, PieceType::queen, PieceType::king}) {
                CHECK(Piece{player, type}.player == player);
                CHECK(Piece{player, type}.type == type);
            }
        }
    }

    SECTION("can construct pieces from letters")
    {
        CHECK(Piece{'-'}.player == Player::none);
        CHECK(Piece{'-'}.type == PieceType::none);

        CHECK(Piece{'p'}.type == PieceType::pawn);
        CHECK(Piece{'n'}.type == PieceType::knight);
        CHECK(Piece{'b'}.type == PieceType::bishop);
        CHECK(Piece{'r'}.type == PieceType::rook);
        CHECK(Piece{'q'}.type == PieceType::queen);
        CHECK(Piece{'k'}.type == PieceType::king);

        CHECK(Piece{'P'}.type == PieceType::pawn);
        CHECK(Piece{'N'}.type == PieceType::knight);
        CHECK(Piece{'B'}.type == PieceType::bishop);
        CHECK(Piece{'R'}.type == PieceType::rook);
        CHECK(Piece{'Q'}.type == PieceType::queen);
        CHECK(Piece{'K'}.type == PieceType::king);

        for (const char letter : {'P', 'N', 'B', 'R', 'Q', 'K'})
            CHECK(Piece{letter}.player == Player::white);

        for (const char letter : {'p', 'n', 'b', 'r', 'q', 'k'})
            CHECK(Piece{letter}.player == Player::black);
    }

    SECTION("no_piece has no player or piece type")
    {
        CHECK(no_piece.player == Player::none);
        CHECK(no_piece.type == PieceType::none);
    }

    SECTION("can compare pieces")
    {
        CHECK(Piece{Player::white, PieceType::rook} == Piece{'R'});
        CHECK(Piece{Player::black, PieceType::king} == Piece{'k'});
        CHECK(Piece{Player::none, PieceType::none} == Piece{'-'});

        CHECK((Piece{Player::white, PieceType::rook} == Piece{Player::black, PieceType::rook}) == false);
        CHECK((Piece{Player::white, PieceType::rook} == Piece{Player::white, PieceType::knight}) == false);
    }
}

}  // namespace chess
