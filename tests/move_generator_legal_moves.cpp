#include "catch2/catch_test_macros.hpp"

#include "../src/move_generator/legal_moves.hpp"

namespace chess {

TEST_CASE("move_generator/legal_moves")
{
    SECTION("is_legal_move()")
    {
        SECTION("check")
        {
            SECTION("white can get out of check by...")
            {
                Board board = Board::create_from_letter_data({
                    "--------",
                    "---P----",
                    "--R-K---",
                    "--------",
                    "-N------",
                    "--------",
                    "b-------",
                    "-----r--",
                });

                SECTION("...capturing the attacking bishop")
                {
                    CHECK(is_legal_move(board, GameState{}, Move::create_capture({"b4"}, {"a2"}, Piece{'N'}, Piece{'b'})));
                }

                SECTION("...moving the king to an unattacked square")
                {
                    CHECK(is_legal_move(board, GameState{}, Move::create_normal({"e6"}, {"e7"}, Piece{'K'})));
                    CHECK(is_legal_move(board, GameState{}, Move::create_normal({"e6"}, {"e5"}, Piece{'K'})));
                    CHECK(is_legal_move(board, GameState{}, Move::create_normal({"e6"}, {"d6"}, Piece{'K'})));

                    CHECK(is_legal_move(board, GameState{}, Move::create_normal({"e6"}, {"f7"}, Piece{'K'})) == false);
                    CHECK(is_legal_move(board, GameState{}, Move::create_normal({"e6"}, {"f6"}, Piece{'K'})) == false);
                    CHECK(is_legal_move(board, GameState{}, Move::create_normal({"e6"}, {"f5"}, Piece{'K'})) == false);
                    CHECK(is_legal_move(board, GameState{}, Move::create_normal({"e6"}, {"d5"}, Piece{'K'})) == false);
                }

                SECTION("...blocking the check")
                {
                    CHECK(is_legal_move(board, GameState{}, Move::create_normal({"c6"}, {"c4"}, Piece{'R'})));
                    CHECK(is_legal_move(board, GameState{}, Move::create_normal({"b4"}, {"d5"}, Piece{'N'})));
                }
            }
        }

        SECTION("castling")
        {
            const auto all_castling_rights = CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_king, CastlingRight::black_queen};

            SECTION("black cannot castle on either side because black is in check by white queen")
            {
                Board board = Board::create_from_letter_data({
                    "r---k--r",
                    "--------",
                    "--------",
                    "-Q------",
                    "--------",
                    "--------",
                    "--------",
                    "--------",
                });

                CHECK(is_legal_move(board, GameState{all_castling_rights, std::nullopt}, Move::create_castling({"e8"}, {"g8"}, Piece{'k'})) == false);
                CHECK(is_legal_move(board, GameState{all_castling_rights, std::nullopt}, Move::create_castling({"e8"}, {"c8"}, Piece{'k'})) == false);
            }

            SECTION("white cannot castle queenside because that would place the king in check")
            {
                Board board = Board::create_from_letter_data({
                    "--------",
                    "--------",
                    "--------",
                    "--q-----",
                    "--------",
                    "--------",
                    "--------",
                    "R---K--R",
                });

                CHECK(is_legal_move(board, GameState{all_castling_rights, std::nullopt}, Move::create_castling({"e1"}, {"c1"}, Piece{'K'})) == false);
            }

            SECTION("white can castle kingside even though the h1 rook is under attack")
            {
                Board board = Board::create_from_letter_data({
                    "--------",
                    "--------",
                    "--q-----",
                    "--------",
                    "--------",
                    "--------",
                    "--------",
                    "R---K--R",
                });

                CHECK(is_legal_move(board, GameState{all_castling_rights, std::nullopt}, Move::create_castling({"e1"}, {"g1"}, Piece{'K'})));
            }

            SECTION("black cannot castle kingside because the white queen attacks f8")
            {
                Board board = Board::create_from_letter_data({
                    "r---k--r",
                    "--------",
                    "--------",
                    "--------",
                    "-----Q--",
                    "--------",
                    "--------",
                    "--------",
                });

                CHECK(is_legal_move(board, GameState{all_castling_rights, std::nullopt}, Move::create_castling({"e8"}, {"g8"}, Piece{'k'})) == false);
            }

            SECTION("black can castle queenside despite the white queen's attack on b8")
            {
                Board board = Board::create_from_letter_data({
                    "r---k--r",
                    "--------",
                    "--------",
                    "--------",
                    "-----Q--",
                    "--------",
                    "--------",
                    "--------",
                });

                CHECK(is_legal_move(board, GameState{all_castling_rights, std::nullopt}, Move::create_castling({"e8"}, {"c8"}, Piece{'k'})));
            }

            SECTION("cannot castle if the castling ability flags aren't set")
            {
                Board board = Board::create_from_letter_data({
                    "r---k--r",
                    "--------",
                    "--------",
                    "--------",
                    "--------",
                    "--------",
                    "--------",
                    "R---K--R",
                });

                CHECK(is_legal_move(board, GameState{}, Move::create_castling({"e8"}, {"c8"}, Piece{'k'})) == false);
                CHECK(is_legal_move(board, GameState{}, Move::create_castling({"e8"}, {"g8"}, Piece{'k'})) == false);
                CHECK(is_legal_move(board, GameState{}, Move::create_castling({"e1"}, {"c1"}, Piece{'K'})) == false);
                CHECK(is_legal_move(board, GameState{}, Move::create_castling({"e1"}, {"g1"}, Piece{'K'})) == false);
            }
        }

        SECTION("en passant")
        {
            Board board = Board::create_from_letter_data({
                "--------",
                "--------",
                "--------",
                "-----Pp-",
                "-Pp-----",
                "--------",
                "--------",
                "--------",
            });

            SECTION("can capture en passant if the en passant target square is set")
            {
                CHECK(is_legal_move(board, GameState{CastlingAbility{}, Square{"g6"}}, Move::create_en_passant({"f5"}, {"g6"}, Piece{'P'})));
                CHECK(is_legal_move(board, GameState{CastlingAbility{}, Square{"b3"}}, Move::create_en_passant({"c4"}, {"b3"}, Piece{'p'})));
            }

            SECTION("cannot capture en passant if the en passant target square is not set")
            {
                CHECK(is_legal_move(board, GameState{CastlingAbility{}, Square{"b3"}}, Move::create_en_passant({"f5"}, {"g6"}, Piece{'P'})) == false);
                CHECK(is_legal_move(board, GameState{CastlingAbility{}, Square{"g6"}}, Move::create_en_passant({"c4"}, {"b3"}, Piece{'p'})) == false);

                CHECK(is_legal_move(board, GameState{}, Move::create_en_passant({"f5"}, {"g6"}, Piece{'P'})) == false);
                CHECK(is_legal_move(board, GameState{}, Move::create_en_passant({"c4"}, {"b3"}, Piece{'p'})) == false);
            }
        }
    }

#if 0
    SECTION("is_check()")
    {
        SECTION("in check from white rook")
        {
            Board board = Board::create_from_letter_data({
                "--------",
                "--------",
                "--------",
                "--k-----",
                "--------",
                "--------",
                "--R-----",
                "--------",
            });

            CHECK(is_check(board, Player::black));
        }

        SECTION("in check from white pawn")
        {
            Board board = Board::create_from_letter_data({
                "--------",
                "--------",
                "--------",
                "--k-----",
                "---P----",
                "--------",
                "--------",
                "--------",
            });

            CHECK(is_check(board, Player::black));
        }

        SECTION("not in check")
        {
            Board board = Board::create_from_letter_data({
                "--------",
                "--------",
                "--------",
                "--k--r-R",
                "---q----",
                "----B---",
                "--------",
                "--------",
            });

            CHECK(is_check(board, Player::black) == false);
        }
    }

    SECTION("is_square_under_attack()")
    {
        SECTION("from rook")
        {
            Board board = Board::create_from_letter_data({
                "--------",
                "--------",
                "--------",
                "-------R",
                "--------",
                "--------",
                "--------",
                "--------",
            });

            CHECK(is_square_under_attack(board, Player::black, Square{"h1"}));
            CHECK(is_square_under_attack(board, Player::black, Square{"h2"}));
            CHECK(is_square_under_attack(board, Player::black, Square{"h7"}));
            CHECK(is_square_under_attack(board, Player::black, Square{"h8"}));
            CHECK(is_square_under_attack(board, Player::black, Square{"a5"}));
            CHECK(is_square_under_attack(board, Player::black, Square{"g5"}));

            CHECK(is_square_under_attack(board, Player::black, Square{"a1"}) == false);
            CHECK(is_square_under_attack(board, Player::black, Square{"a8"}) == false);
        }

        SECTION("from knight")
        {
            Board board = Board::create_from_letter_data({
                "--------",
                "--------",
                "--------",
                "--------",
                "--------",
                "-----N--",
                "--------",
                "--------",
            });

            CHECK(is_square_under_attack(board, Player::black, Square{"d4"}));
            CHECK(is_square_under_attack(board, Player::black, Square{"e1"}));

            CHECK(is_square_under_attack(board, Player::black, Square{"a1"}) == false);
            CHECK(is_square_under_attack(board, Player::black, Square{"a8"}) == false);
        }
    }
#endif
}

}  // namespace chess
