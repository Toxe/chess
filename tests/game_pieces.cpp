#include "catch2/catch_test_macros.hpp"

#include "../src/game/pieces.hpp"

namespace chess {

TEST_CASE("game/pieces")
{
    SECTION("can construct Piece with Player and PieceType")
    {
        for (const auto player : {Player::none, Player::white, Player::black}) {
            for (const auto type : {PieceType::none, PieceType::pawn, PieceType::knight, PieceType::bishop, PieceType::rook, PieceType::queen, PieceType::king}) {
                CHECK(Piece{player, type}.player == player);
                CHECK(Piece{player, type}.type == type);
            }
        }
    }

    SECTION("can construct Piece from char")
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

        for (const char c : {'P', 'N', 'B', 'R', 'Q', 'K'})
            CHECK(Piece{c}.player == Player::white);

        for (const char c : {'p', 'n', 'b', 'r', 'q', 'k'})
            CHECK(Piece{c}.player == Player::black);
    }

    SECTION("can construct pieces from Player and char")
    {
        for (const auto player : {Player::none, Player::white, Player::black}) {
            CHECK(Piece{player, '-'} == Piece{player, PieceType::none});
            CHECK(Piece{player, 'p'} == Piece{player, PieceType::pawn});
            CHECK(Piece{player, 'P'} == Piece{player, PieceType::pawn});
            CHECK(Piece{player, 'n'} == Piece{player, PieceType::knight});
            CHECK(Piece{player, 'N'} == Piece{player, PieceType::knight});
            CHECK(Piece{player, 'b'} == Piece{player, PieceType::bishop});
            CHECK(Piece{player, 'B'} == Piece{player, PieceType::bishop});
            CHECK(Piece{player, 'r'} == Piece{player, PieceType::rook});
            CHECK(Piece{player, 'R'} == Piece{player, PieceType::rook});
            CHECK(Piece{player, 'q'} == Piece{player, PieceType::queen});
            CHECK(Piece{player, 'Q'} == Piece{player, PieceType::queen});
            CHECK(Piece{player, 'k'} == Piece{player, PieceType::king});
            CHECK(Piece{player, 'K'} == Piece{player, PieceType::king});
        }
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

    SECTION("return PieceType from char")
    {
        CHECK(piece_type_from_char('p') == PieceType::pawn);
        CHECK(piece_type_from_char('P') == PieceType::pawn);
        CHECK(piece_type_from_char('n') == PieceType::knight);
        CHECK(piece_type_from_char('N') == PieceType::knight);
        CHECK(piece_type_from_char('b') == PieceType::bishop);
        CHECK(piece_type_from_char('B') == PieceType::bishop);
        CHECK(piece_type_from_char('r') == PieceType::rook);
        CHECK(piece_type_from_char('R') == PieceType::rook);
        CHECK(piece_type_from_char('q') == PieceType::queen);
        CHECK(piece_type_from_char('Q') == PieceType::queen);
        CHECK(piece_type_from_char('k') == PieceType::king);
        CHECK(piece_type_from_char('K') == PieceType::king);
        CHECK(piece_type_from_char('-') == PieceType::none);
        CHECK(piece_type_from_char('?') == PieceType::none);
        CHECK(piece_type_from_char('1') == PieceType::none);
    }
}

}  // namespace chess
