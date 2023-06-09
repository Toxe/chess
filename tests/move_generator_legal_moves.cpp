#include "catch2/catch_test_macros.hpp"

#include "../src/move_generator/legal_moves.hpp"

namespace chess {

TEST_CASE("move_generator/legal_moves")
{
    SECTION("check_legal_move()")
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
                    CHECK(check_legal_move(board, GameState{}, Move::create_capture({"b4"}, {"a2"}, Piece{'N'}, Piece{'b'})) == MoveLegality::ok);
                }

                SECTION("...moving the king to an unattacked square")
                {
                    CHECK(check_legal_move(board, GameState{}, Move::create_normal({"e6"}, {"e7"}, Piece{'K'})) == MoveLegality::ok);
                    CHECK(check_legal_move(board, GameState{}, Move::create_normal({"e6"}, {"e5"}, Piece{'K'})) == MoveLegality::ok);
                    CHECK(check_legal_move(board, GameState{}, Move::create_normal({"e6"}, {"d6"}, Piece{'K'})) == MoveLegality::ok);

                    CHECK(check_legal_move(board, GameState{}, Move::create_normal({"e6"}, {"f7"}, Piece{'K'})) == MoveLegality::would_result_in_check);
                    CHECK(check_legal_move(board, GameState{}, Move::create_normal({"e6"}, {"f6"}, Piece{'K'})) == MoveLegality::would_result_in_check);
                    CHECK(check_legal_move(board, GameState{}, Move::create_normal({"e6"}, {"f5"}, Piece{'K'})) == MoveLegality::would_result_in_check);
                    CHECK(check_legal_move(board, GameState{}, Move::create_normal({"e6"}, {"d5"}, Piece{'K'})) == MoveLegality::would_result_in_check);
                }

                SECTION("...blocking the check")
                {
                    CHECK(check_legal_move(board, GameState{}, Move::create_normal({"c6"}, {"c4"}, Piece{'R'})) == MoveLegality::ok);
                    CHECK(check_legal_move(board, GameState{}, Move::create_normal({"b4"}, {"d5"}, Piece{'N'})) == MoveLegality::ok);
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

                CHECK(check_legal_move(board, GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_castling({"e8"}, {"g8"}, Piece{'k'})) == MoveLegality::check);
                CHECK(check_legal_move(board, GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_castling({"e8"}, {"c8"}, Piece{'k'})) == MoveLegality::check);
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

                CHECK(check_legal_move(board, GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_castling({"e1"}, {"c1"}, Piece{'K'})) == MoveLegality::would_result_in_check);
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

                CHECK(check_legal_move(board, GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_castling({"e1"}, {"g1"}, Piece{'K'})) == MoveLegality::ok);
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

                CHECK(check_legal_move(board, GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_castling({"e8"}, {"g8"}, Piece{'k'})) == MoveLegality::square_under_attack);
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

                CHECK(check_legal_move(board, GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_castling({"e8"}, {"c8"}, Piece{'k'})) == MoveLegality::ok);
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

                CHECK(check_legal_move(board, GameState{}, Move::create_castling({"e8"}, {"c8"}, Piece{'k'})) == MoveLegality::no_castling_ability);
                CHECK(check_legal_move(board, GameState{}, Move::create_castling({"e8"}, {"g8"}, Piece{'k'})) == MoveLegality::no_castling_ability);
                CHECK(check_legal_move(board, GameState{}, Move::create_castling({"e1"}, {"c1"}, Piece{'K'})) == MoveLegality::no_castling_ability);
                CHECK(check_legal_move(board, GameState{}, Move::create_castling({"e1"}, {"g1"}, Piece{'K'})) == MoveLegality::no_castling_ability);
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
                CHECK(check_legal_move(board, GameState{0, 1, CastlingAbility{}, Square{"g6"}}, Move::create_en_passant({"f5"}, {"g6"}, Piece{'P'})) == MoveLegality::ok);
                CHECK(check_legal_move(board, GameState{0, 1, CastlingAbility{}, Square{"b3"}}, Move::create_en_passant({"c4"}, {"b3"}, Piece{'p'})) == MoveLegality::ok);
            }

            SECTION("cannot capture en passant if the en passant target square is not set")
            {
                CHECK(check_legal_move(board, GameState{0, 1, CastlingAbility{}, Square{"b3"}}, Move::create_en_passant({"f5"}, {"g6"}, Piece{'P'})) == MoveLegality::en_passant_target_square_wrong);
                CHECK(check_legal_move(board, GameState{0, 1, CastlingAbility{}, Square{"g6"}}, Move::create_en_passant({"c4"}, {"b3"}, Piece{'p'})) == MoveLegality::en_passant_target_square_wrong);

                CHECK(check_legal_move(board, GameState{}, Move::create_en_passant({"f5"}, {"g6"}, Piece{'P'})) == MoveLegality::en_passant_target_square_not_set);
                CHECK(check_legal_move(board, GameState{}, Move::create_en_passant({"c4"}, {"b3"}, Piece{'p'})) == MoveLegality::en_passant_target_square_not_set);
            }
        }
    }
}

}  // namespace chess
