#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../src/game/print.hpp"

namespace chess {

TEST_CASE("game/print")
{
    SECTION("print_player()")
    {
        CHECK(print_player(Player::white) == "white");
        CHECK(print_player(Player::black) == "black");
    }

    SECTION("print_player_side()")
    {
        CHECK(print_player_side(Player::white) == "White");
        CHECK(print_player_side(Player::black) == "Black");
    }

    SECTION("print_piece_type()")
    {
        CHECK(print_piece_type(PieceType::pawn) == "pawn");
        CHECK(print_piece_type(PieceType::knight) == "knight");
        CHECK(print_piece_type(PieceType::bishop) == "bishop");
        CHECK(print_piece_type(PieceType::rook) == "rook");
        CHECK(print_piece_type(PieceType::queen) == "queen");
        CHECK(print_piece_type(PieceType::king) == "king");
    }

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

    SECTION("print_game_over()")
    {
        SECTION("game is not over")
        {
            CHECK_THAT(print_game_over(WinCondition::none), Catch::Matchers::Equals("The game is not over yet."));
        }

        SECTION("draw")
        {
            CHECK_THAT(print_game_over(WinCondition::draw), Catch::Matchers::Equals("Draw!"));
        }

        SECTION("White won")
        {
            CHECK_THAT(print_game_over(WinCondition::player1_won), Catch::Matchers::Equals("White won!"));
        }

        SECTION("Black won")
        {
            CHECK_THAT(print_game_over(WinCondition::player2_won), Catch::Matchers::Equals("Black won!"));
        }
    }
}

}  // namespace chess