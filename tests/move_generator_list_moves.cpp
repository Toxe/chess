#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_contains.hpp"

#include "../src/move_generator/list_moves.hpp"
#include "../src/move_generator/list_moves_detail.hpp"

namespace chess {

using namespace detail::list_moves;

TEST_CASE("move_generator/list_moves")
{
    SECTION("list_moves()")
    {
        SECTION("default board")
        {
            const auto moves_white = list_moves(Player::white, Board::create_with_default_pieces());
            const auto moves_black = list_moves(Player::black, Board::create_with_default_pieces());

            CHECK(moves_white.size() == 20);
            CHECK(moves_black.size() == 20);
            CHECK(count_moves(moves_white, MoveType::normal) == 20);
            CHECK(count_moves(moves_black, MoveType::normal) == 20);
        }

        SECTION("arbitrary board")
        {
            const Board board = Board::create_from_letter_data({
                "r-b-k--r",
                "-p------",
                "-----p--",
                "-Pp--P--",
                "-RP-N--b",
                "---n--Q-",
                "-----K-p",
                "R-----B-",
            });

            const auto moves_white = list_moves(Player::white, board);
            const auto moves_black = list_moves(Player::black, board);

            CHECK(moves_white.size() == 48);
            CHECK(count_moves(moves_white, MoveType::normal) == 40);
            CHECK(count_moves(moves_white, MoveType::promotion) == 0);
            CHECK(count_moves(moves_white, MoveType::capture) == 7);
            CHECK(count_moves(moves_white, MoveType::capture_and_promotion) == 0);
            CHECK(count_moves(moves_white, MoveType::castling) == 0);
            CHECK(count_moves(moves_white, MoveType::en_passant) == 1);

            CHECK(moves_black.size() == 41);
            CHECK(count_moves(moves_black, MoveType::normal) == 26);
            CHECK(count_moves(moves_black, MoveType::promotion) == 4);
            CHECK(count_moves(moves_black, MoveType::capture) == 6);
            CHECK(count_moves(moves_black, MoveType::capture_and_promotion) == 4);
            CHECK(count_moves(moves_black, MoveType::castling) == 1);
            CHECK(count_moves(moves_black, MoveType::en_passant) == 0);
        }
    }

    SECTION("detail")
    {
        SECTION("list moves for each piece type")
        {
            Moves moves;

            SECTION("pawn")
            {
                const Board board = Board::create_from_letter_data({
                    "r-------",
                    "PP-ppp--",
                    "-----n-p",
                    "PpP-n-N-",
                    "---n----",
                    "---PP---",
                    "--------",
                    "--------",
                });

                CHECK(list_moves_for_pawn(board, BoardPiece{Piece{'P'}, Square{"a7"}}, moves) == 0);
                CHECK(list_moves_for_pawn(board, BoardPiece{Piece{'P'}, Square{"b7"}}, moves) == 8);
                CHECK(list_moves_for_pawn(board, BoardPiece{Piece{'p'}, Square{"d7"}}, moves) == 2);
                CHECK(list_moves_for_pawn(board, BoardPiece{Piece{'p'}, Square{"e7"}}, moves) == 1);
                CHECK(list_moves_for_pawn(board, BoardPiece{Piece{'p'}, Square{"f7"}}, moves) == 0);
                CHECK(list_moves_for_pawn(board, BoardPiece{Piece{'p'}, Square{"h6"}}, moves) == 2);
                CHECK(list_moves_for_pawn(board, BoardPiece{Piece{'P'}, Square{"a5"}}, moves) == 2);
                CHECK(list_moves_for_pawn(board, BoardPiece{Piece{'p'}, Square{"b5"}}, moves) == 1);
                CHECK(list_moves_for_pawn(board, BoardPiece{Piece{'P'}, Square{"c5"}}, moves) == 2);
                CHECK(list_moves_for_pawn(board, BoardPiece{Piece{'P'}, Square{"d3"}}, moves) == 0);
                CHECK(list_moves_for_pawn(board, BoardPiece{Piece{'P'}, Square{"e3"}}, moves) == 2);

                CHECK(moves.size() == 20);
                CHECK(count_moves(moves, MoveType::normal) == 8);
                CHECK(count_moves(moves, MoveType::promotion) == 4);
                CHECK(count_moves(moves, MoveType::capture) == 2);
                CHECK(count_moves(moves, MoveType::capture_and_promotion) == 4);
                CHECK(count_moves(moves, MoveType::en_passant) == 2);
            }

            SECTION("knight")
            {
                const Board board = Board::create_from_letter_data({
                    "n-------",
                    "--------",
                    "---p----",
                    "--n-r-p-",
                    "---rN---",
                    "--------",
                    "---R-R--",
                    "--------",
                });

                CHECK(list_moves_for_knight(board, BoardPiece{Piece{'n'}, Square{"a8"}}, moves) == 2);
                CHECK(list_moves_for_knight(board, BoardPiece{Piece{'n'}, Square{"c5"}}, moves) == 8);
                CHECK(list_moves_for_knight(board, BoardPiece{Piece{'N'}, Square{"e4"}}, moves) == 6);

                CHECK(moves.size() == 16);
                CHECK(count_moves(moves, MoveType::normal) == 12);
                CHECK(count_moves(moves, MoveType::capture) == 4);
            }

            SECTION("bishop")
            {
                const Board board = Board::create_from_letter_data({
                    "N------b",
                    "---N---b",
                    "--b-----",
                    "-N------",
                    "N---N---",
                    "-n------",
                    "--B-----",
                    "-n-----N",
                });

                CHECK(list_moves_for_bishop(board, BoardPiece{Piece{'b'}, Square{"h8"}}, moves) == 7);
                CHECK(list_moves_for_bishop(board, BoardPiece{Piece{'b'}, Square{"h7"}}, moves) == 4);
                CHECK(list_moves_for_bishop(board, BoardPiece{Piece{'b'}, Square{"c6"}}, moves) == 6);
                CHECK(list_moves_for_bishop(board, BoardPiece{Piece{'B'}, Square{"c2"}}, moves) == 4);

                CHECK(moves.size() == 21);
                CHECK(count_moves(moves, MoveType::normal) == 14);
                CHECK(count_moves(moves, MoveType::capture) == 7);
            }

            SECTION("rook")
            {
                const Board board = Board::create_from_letter_data({
                    "rP----pR",
                    "---nN---",
                    "P--rR--p",
                    "---nN---",
                    "--------",
                    "--------",
                    "--------",
                    "-------R",
                });

                CHECK(list_moves_for_rook(board, BoardPiece{Piece{'r'}, Square{"a8"}}, moves) == 3);
                CHECK(list_moves_for_rook(board, BoardPiece{Piece{'R'}, Square{"h8"}}, moves) == 3);
                CHECK(list_moves_for_rook(board, BoardPiece{Piece{'r'}, Square{"d6"}}, moves) == 4);
                CHECK(list_moves_for_rook(board, BoardPiece{Piece{'R'}, Square{"e6"}}, moves) == 4);
                CHECK(list_moves_for_rook(board, BoardPiece{Piece{'R'}, Square{"h1"}}, moves) == 12);

                CHECK(moves.size() == 26);
                CHECK(count_moves(moves, MoveType::normal) == 17);
                CHECK(count_moves(moves, MoveType::capture) == 9);
            }

            SECTION("queen")
            {
                const Board board = Board::create_from_letter_data({
                    "N-------",
                    "---N---q",
                    "--q-----",
                    "-N------",
                    "N---N---",
                    "-n------",
                    "--Q-----",
                    "-n-----N",
                });

                CHECK(list_moves_for_queen(board, BoardPiece{Piece{'q'}, Square{"c6"}}, moves) == 19);
                CHECK(list_moves_for_queen(board, BoardPiece{Piece{'q'}, Square{"h7"}}, moves) == 15);
                CHECK(list_moves_for_queen(board, BoardPiece{Piece{'Q'}, Square{"c2"}}, moves) == 16);

                CHECK(moves.size() == 50);
                CHECK(count_moves(moves, MoveType::normal) == 39);
                CHECK(count_moves(moves, MoveType::capture) == 11);
            }

            SECTION("king")
            {
                const Board board = Board::create_from_letter_data({
                    "rn--k--r",
                    "----N---",
                    "-n------",
                    "-nkP----",
                    "---P----",
                    "--------",
                    "---nN--R",
                    "R---K--r",
                });

                CHECK(list_moves_for_king(board, BoardPiece{Piece{'k'}, Square{"e8"}}, moves) == 6);
                CHECK(list_moves_for_king(board, BoardPiece{Piece{'k'}, Square{"c5"}}, moves) == 6);
                CHECK(list_moves_for_king(board, BoardPiece{Piece{'K'}, Square{"e1"}}, moves) == 5);

                CHECK(moves.size() == 17);
                CHECK(count_moves(moves, MoveType::normal) == 11);
                CHECK(count_moves(moves, MoveType::capture) == 4);
                CHECK(count_moves(moves, MoveType::castling) == 2);
            }
        }

        SECTION("move creation functions")
        {
            Moves moves;

            SECTION("list_moves_for_piece()")
            {
                const Board board = Board::create_from_letter_data({
                    "------r-",
                    "-bp-----",
                    "--------",
                    "--------",
                    "----P---",
                    "------N-",
                    "----K-Q-",
                    "--------",
                });

                CHECK(list_moves_for_piece(board, BoardPiece{Piece{'p'}, Square{"c7"}}, moves) == 2);
                CHECK(list_moves_for_piece(board, BoardPiece{Piece{'b'}, Square{"b7"}}, moves) == 6);
                CHECK(list_moves_for_piece(board, BoardPiece{Piece{'r'}, Square{"g8"}}, moves) == 12);
                CHECK(list_moves_for_piece(board, BoardPiece{Piece{'P'}, Square{"e4"}}, moves) == 1);
                CHECK(list_moves_for_piece(board, BoardPiece{Piece{'N'}, Square{"g3"}}, moves) == 4);
                CHECK(list_moves_for_piece(board, BoardPiece{Piece{'K'}, Square{"e2"}}, moves) == 8);
                CHECK(list_moves_for_piece(board, BoardPiece{Piece{'Q'}, Square{"g2"}}, moves) == 7);

                CHECK(moves.size() == 40);
                CHECK(count_moves(moves, MoveType::normal) == 38);
                CHECK(count_moves(moves, MoveType::capture) == 2);
            }

            SECTION("create_straight_line_moves()")
            {
                SECTION("horizontal and vertical")
                {
                    const Board board = Board::create_from_letter_data({
                        "--N-----",
                        "-----n--",
                        "--r-----",
                        "--------",
                        "--------",
                        "---n-R-N",
                        "-----n--",
                        "--------",
                    });

                    CHECK(create_straight_line_moves(board, BoardPiece{Piece{'r'}, Square{"c6"}}, moves, 1, {-1, 0}) == 1);  // note: limited move range, for testing
                    CHECK(create_straight_line_moves(board, BoardPiece{Piece{'r'}, Square{"c6"}}, moves, 2, {1, 0}) == 2);  // note: limited move range, for testing
                    CHECK(create_straight_line_moves(board, BoardPiece{Piece{'r'}, Square{"c6"}}, moves, 8, {0, -1}) == 2);
                    CHECK(create_straight_line_moves(board, BoardPiece{Piece{'r'}, Square{"c6"}}, moves, 8, {0, 1}) == 5);

                    CHECK(create_straight_line_moves(board, BoardPiece{Piece{'R'}, Square{"f3"}}, moves, 8, {-1, 0}) == 2);
                    CHECK(create_straight_line_moves(board, BoardPiece{Piece{'R'}, Square{"f3"}}, moves, 8, {1, 0}) == 1);
                    CHECK(create_straight_line_moves(board, BoardPiece{Piece{'R'}, Square{"f3"}}, moves, 8, {0, -1}) == 4);
                    CHECK(create_straight_line_moves(board, BoardPiece{Piece{'R'}, Square{"f3"}}, moves, 8, {0, 1}) == 1);

                    CHECK(moves.size() == 18);
                    CHECK(count_moves(moves, MoveType::normal) == 14);
                    CHECK(count_moves(moves, MoveType::capture) == 4);
                }

                SECTION("diagonal")
                {
                    const Board board = Board::create_from_letter_data({
                        "----n--b",
                        "--------",
                        "--b-----",
                        "-N------",
                        "----N---",
                        "-------n",
                        "------B-",
                        "--------",
                    });

                    CHECK(create_straight_line_moves(board, BoardPiece{Piece{'b'}, Square{"c6"}}, moves, 1, {-1, -1}) == 1);  // note: limited move range, for testing
                    CHECK(create_straight_line_moves(board, BoardPiece{Piece{'b'}, Square{"c6"}}, moves, 8, {-1, 1}) == 1);
                    CHECK(create_straight_line_moves(board, BoardPiece{Piece{'b'}, Square{"c6"}}, moves, 8, {1, -1}) == 1);
                    CHECK(create_straight_line_moves(board, BoardPiece{Piece{'b'}, Square{"c6"}}, moves, 8, {1, 1}) == 2);

                    CHECK(create_straight_line_moves(board, BoardPiece{Piece{'B'}, Square{"g2"}}, moves, 8, {-1, -1}) == 1);
                    CHECK(create_straight_line_moves(board, BoardPiece{Piece{'B'}, Square{"g2"}}, moves, 8, {-1, 1}) == 1);
                    CHECK(create_straight_line_moves(board, BoardPiece{Piece{'B'}, Square{"g2"}}, moves, 8, {1, -1}) == 1);
                    CHECK(create_straight_line_moves(board, BoardPiece{Piece{'B'}, Square{"g2"}}, moves, 8, {1, 1}) == 1);

                    CHECK(moves.size() == 9);
                    CHECK(count_moves(moves, MoveType::normal) == 6);
                    CHECK(count_moves(moves, MoveType::capture) == 3);
                }
            }

            SECTION("create_pawn_forward_moves()")
            {
                SECTION("move forward from second rank")
                {
                    const Board board = Board::create_from_letter_data({
                        "--------",
                        "ppp--p--",
                        "--n--N--",
                        "-n------",
                        "-N------",
                        "--N--n--",
                        "PPP--P--",
                        "--------",
                    });

                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'p'}, Square{"a7"}}, moves) == 2);
                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'p'}, Square{"b7"}}, moves) == 1);
                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'p'}, Square{"c7"}}, moves) == 0);
                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'p'}, Square{"f7"}}, moves) == 0);
                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'P'}, Square{"a2"}}, moves) == 2);
                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'P'}, Square{"b2"}}, moves) == 1);
                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'P'}, Square{"c2"}}, moves) == 0);
                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'P'}, Square{"f2"}}, moves) == 0);

                    CHECK(moves.size() == 6);
                    CHECK(count_moves(moves, MoveType::normal) == 6);
                }

                SECTION("move forward from non-second ranks")
                {
                    const Board board = Board::create_from_letter_data({
                        "----P---",
                        "--------",
                        "pp--p---",
                        "-n--N---",
                        "-N--n---",
                        "PP--P---",
                        "--------",
                        "----p---",
                    });

                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'P'}, Square{"e8"}}, moves) == 0);
                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'p'}, Square{"a6"}}, moves) == 1);
                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'p'}, Square{"b6"}}, moves) == 0);
                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'p'}, Square{"e6"}}, moves) == 0);
                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'P'}, Square{"a3"}}, moves) == 1);
                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'P'}, Square{"b3"}}, moves) == 0);
                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'P'}, Square{"e3"}}, moves) == 0);
                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'p'}, Square{"e1"}}, moves) == 0);

                    CHECK(moves.size() == 2);
                    CHECK(count_moves(moves, MoveType::normal) == 2);
                }

                SECTION("promotion from 7th rank")
                {
                    const Board board = Board::create_from_letter_data({
                        "--n-----",
                        "P-P---p-",
                        "--------",
                        "--------",
                        "--------",
                        "--------",
                        "P---p-p-",
                        "----N---",
                    });

                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'P'}, Square{"a7"}}, moves) == 4);
                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'P'}, Square{"c7"}}, moves) == 0);
                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'p'}, Square{"g7"}}, moves) == 2);

                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'P'}, Square{"a2"}}, moves) == 2);
                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'p'}, Square{"e2"}}, moves) == 0);
                    CHECK(create_pawn_forward_moves(board, BoardPiece{Piece{'p'}, Square{"g2"}}, moves) == 4);

                    CHECK(moves.size() == 12);
                    CHECK(count_moves(moves, MoveType::promotion) == 8);

                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"a7"}, {"a8"}, Piece{'N'}, MoveType::promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"a7"}, {"a8"}, Piece{'R'}, MoveType::promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"a7"}, {"a8"}, Piece{'B'}, MoveType::promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"a7"}, {"a8"}, Piece{'Q'}, MoveType::promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"g2"}, {"g1"}, Piece{'n'}, MoveType::promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"g2"}, {"g1"}, Piece{'r'}, MoveType::promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"g2"}, {"g1"}, Piece{'b'}, MoveType::promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"g2"}, {"g1"}, Piece{'q'}, MoveType::promotion}));
                }
            }

            SECTION("create_pawn_capture_moves()")
            {
                SECTION("normal capture")
                {
                    const Board board = Board::create_from_letter_data({
                        "--------",
                        "pp---p-p",
                        "NNN---Nn",
                        "---nNn--",
                        "----P-rr",
                        "-----r--",
                        "-----PPP",
                        "--------",
                    });

                    CHECK(create_pawn_capture_moves(board, BoardPiece{Piece{'p'}, Square{"a7"}}, moves) == 1);
                    CHECK(create_pawn_capture_moves(board, BoardPiece{Piece{'p'}, Square{"b7"}}, moves) == 2);
                    CHECK(create_pawn_capture_moves(board, BoardPiece{Piece{'p'}, Square{"f7"}}, moves) == 1);
                    CHECK(create_pawn_capture_moves(board, BoardPiece{Piece{'p'}, Square{"h7"}}, moves) == 1);
                    CHECK(create_pawn_capture_moves(board, BoardPiece{Piece{'P'}, Square{"e4"}}, moves) == 2);
                    CHECK(create_pawn_capture_moves(board, BoardPiece{Piece{'P'}, Square{"f2"}}, moves) == 0);
                    CHECK(create_pawn_capture_moves(board, BoardPiece{Piece{'P'}, Square{"g2"}}, moves) == 1);
                    CHECK(create_pawn_capture_moves(board, BoardPiece{Piece{'P'}, Square{"h2"}}, moves) == 0);

                    CHECK(moves.size() == 8);
                    CHECK(count_moves(moves, MoveType::capture) == 8);
                }

                SECTION("capture + promotion from 7th rank")
                {
                    const Board board = Board::create_from_letter_data({
                        "-r----r-",
                        "P------P",
                        "--------",
                        "--------",
                        "--------",
                        "--------",
                        "----p---",
                        "---R-R--",
                    });

                    CHECK(create_pawn_capture_moves(board, BoardPiece{Piece{'P'}, Square{"a7"}}, moves) == 4);
                    CHECK(create_pawn_capture_moves(board, BoardPiece{Piece{'P'}, Square{"h7"}}, moves) == 4);
                    CHECK(create_pawn_capture_moves(board, BoardPiece{Piece{'p'}, Square{"e2"}}, moves) == 8);

                    CHECK(moves.size() == 16);
                    CHECK(count_moves(moves, MoveType::capture_and_promotion) == 16);

                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"a7"}, {"b8"}, Piece{'N'}, MoveType::capture_and_promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"a7"}, {"b8"}, Piece{'R'}, MoveType::capture_and_promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"a7"}, {"b8"}, Piece{'B'}, MoveType::capture_and_promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"a7"}, {"b8"}, Piece{'Q'}, MoveType::capture_and_promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"h7"}, {"g8"}, Piece{'N'}, MoveType::capture_and_promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"h7"}, {"g8"}, Piece{'R'}, MoveType::capture_and_promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"h7"}, {"g8"}, Piece{'B'}, MoveType::capture_and_promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"h7"}, {"g8"}, Piece{'Q'}, MoveType::capture_and_promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"e2"}, {"d1"}, Piece{'n'}, MoveType::capture_and_promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"e2"}, {"d1"}, Piece{'r'}, MoveType::capture_and_promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"e2"}, {"d1"}, Piece{'b'}, MoveType::capture_and_promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"e2"}, {"d1"}, Piece{'q'}, MoveType::capture_and_promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"e2"}, {"f1"}, Piece{'n'}, MoveType::capture_and_promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"e2"}, {"f1"}, Piece{'r'}, MoveType::capture_and_promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"e2"}, {"f1"}, Piece{'b'}, MoveType::capture_and_promotion}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"e2"}, {"f1"}, Piece{'q'}, MoveType::capture_and_promotion}));
                }
            }

            SECTION("create_pawn_en_passant_moves()")
            {
                SECTION("only possible from 5th rank")
                {
                    const Board board = Board::create_from_letter_data({
                        "--------",
                        "--------",
                        "--------",
                        "PpP-----",
                        "----pPp-",
                        "--------",
                        "--------",
                        "--------",
                    });

                    // en passant for white
                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'P'}, Square{"a5"}}, moves) == 1);
                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'p'}, Square{"b5"}}, moves) == 0);
                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'P'}, Square{"c5"}}, moves) == 1);

                    // en passant for black
                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'p'}, Square{"e4"}}, moves) == 1);
                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'P'}, Square{"f4"}}, moves) == 0);
                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'p'}, Square{"g4"}}, moves) == 1);

                    CHECK(moves.size() == 4);
                    CHECK(count_moves(moves, MoveType::en_passant) == 4);

                    CHECK_THAT(moves, Catch::Matchers::Contains(Move::create_en_passant({"a5"}, {"b6"}, Piece{'P'})));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move::create_en_passant({"c5"}, {"b6"}, Piece{'P'})));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move::create_en_passant({"e4"}, {"f3"}, Piece{'p'})));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move::create_en_passant({"g4"}, {"f3"}, Piece{'p'})));
                }

                SECTION("impossible when not on 5th rank")
                {
                    const Board board = Board::create_from_letter_data({
                        "--------",
                        "PpP-----",
                        "-----pPp",
                        "--------",
                        "--------",
                        "--------",
                        "--pPp---",
                        "--------",
                    });

                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'P'}, Square{"a7"}}, moves) == 0);
                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'p'}, Square{"b7"}}, moves) == 0);
                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'P'}, Square{"c7"}}, moves) == 0);

                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'p'}, Square{"f6"}}, moves) == 0);
                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'P'}, Square{"g6"}}, moves) == 0);
                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'p'}, Square{"h6"}}, moves) == 0);

                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'p'}, Square{"c2"}}, moves) == 0);
                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'P'}, Square{"d2"}}, moves) == 0);
                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'p'}, Square{"e2"}}, moves) == 0);

                    CHECK(moves.size() == 0);
                }

                SECTION("destination square must not be occupied")
                {
                    const Board board = Board::create_from_letter_data({
                        "--------",
                        "--------",
                        "-n------",
                        "PpP-----",
                        "----pPp-",
                        "-----n--",
                        "--------",
                        "--------",
                    });

                    // en passant for white
                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'P'}, Square{"a5"}}, moves) == 0);
                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'P'}, Square{"c5"}}, moves) == 0);

                    // en passant for black
                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'p'}, Square{"e4"}}, moves) == 0);
                    CHECK(create_pawn_en_passant_moves(board, BoardPiece{Piece{'p'}, Square{"g4"}}, moves) == 0);

                    CHECK(moves.size() == 0);
                }
            }

            SECTION("create_knight_move()")
            {
                SECTION("normal move")
                {
                    const Board board = Board::create_from_letter_data({
                        "-------n",
                        "-n------",
                        "--------",
                        "--------",
                        "--------",
                        "----N---",
                        "--------",
                        "--------",
                    });

                    CHECK(create_knight_move(board, BoardPiece{Piece{'n'}, Square{"h8"}}, moves, MoveOffset{2, -1}) == 0);
                    CHECK(create_knight_move(board, BoardPiece{Piece{'n'}, Square{"h8"}}, moves, MoveOffset{2, 1}) == 0);
                    CHECK(create_knight_move(board, BoardPiece{Piece{'n'}, Square{"h8"}}, moves, MoveOffset{-2, -1}) == 0);
                    CHECK(create_knight_move(board, BoardPiece{Piece{'n'}, Square{"h8"}}, moves, MoveOffset{-2, 1}) == 1);

                    CHECK(create_knight_move(board, BoardPiece{Piece{'n'}, Square{"b7"}}, moves, MoveOffset{2, -1}) == 1);
                    CHECK(create_knight_move(board, BoardPiece{Piece{'n'}, Square{"b7"}}, moves, MoveOffset{2, 1}) == 1);
                    CHECK(create_knight_move(board, BoardPiece{Piece{'n'}, Square{"b7"}}, moves, MoveOffset{-1, 2}) == 1);

                    CHECK(create_knight_move(board, BoardPiece{Piece{'N'}, Square{"e3"}}, moves, MoveOffset{1, -2}) == 1);
                    CHECK(create_knight_move(board, BoardPiece{Piece{'N'}, Square{"e3"}}, moves, MoveOffset{2, 1}) == 1);
                    CHECK(create_knight_move(board, BoardPiece{Piece{'N'}, Square{"e3"}}, moves, MoveOffset{1, 2}) == 1);

                    CHECK(moves.size() == 7);
                    CHECK(count_moves(moves, MoveType::normal) == 7);
                }

                SECTION("capture")
                {
                    const Board board = Board::create_from_letter_data({
                        "--------",
                        "---p----",
                        "R---p---",
                        "--n-----",
                        "----N---",
                        "--R-----",
                        "---r-r--",
                        "--------",
                    });

                    CHECK(create_knight_move(board, BoardPiece{Piece{'n'}, Square{"c5"}}, moves, MoveOffset{2, 1}) == 1);
                    CHECK(create_knight_move(board, BoardPiece{Piece{'n'}, Square{"c5"}}, moves, MoveOffset{-2, -1}) == 1);
                    CHECK(create_knight_move(board, BoardPiece{Piece{'n'}, Square{"c5"}}, moves, MoveOffset{1, -2}) == 0);
                    CHECK(create_knight_move(board, BoardPiece{Piece{'n'}, Square{"c5"}}, moves, MoveOffset{2, -1}) == 0);
                    CHECK(create_knight_move(board, BoardPiece{Piece{'N'}, Square{"e4"}}, moves, MoveOffset{1, 2}) == 1);
                    CHECK(create_knight_move(board, BoardPiece{Piece{'N'}, Square{"e4"}}, moves, MoveOffset{-1, 2}) == 1);
                    CHECK(create_knight_move(board, BoardPiece{Piece{'N'}, Square{"e4"}}, moves, MoveOffset{-2, 1}) == 0);

                    CHECK(moves.size() == 4);
                    CHECK(count_moves(moves, MoveType::capture) == 4);
                }
            }

            SECTION("create_king_castling_moves()")
            {
                SECTION("possible")
                {
                    const Board board = Board::create_from_letter_data({
                        "r---k--r",
                        "--------",
                        "--------",
                        "--------",
                        "--------",
                        "--------",
                        "--------",
                        "R---K--R",
                    });

                    CHECK(create_king_castling_moves(board, BoardPiece{Piece{'k'}, Square{"e8"}}, moves) == 2);
                    CHECK(create_king_castling_moves(board, BoardPiece{Piece{'K'}, Square{"e1"}}, moves) == 2);

                    CHECK(moves.size() == 4);
                    CHECK(count_moves(moves, MoveType::castling) == 4);

                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"e8"}, {"g8"}, Piece{'k'}, MoveType::castling}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"e8"}, {"c8"}, Piece{'k'}, MoveType::castling}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"e1"}, {"g1"}, Piece{'K'}, MoveType::castling}));
                    CHECK_THAT(moves, Catch::Matchers::Contains(Move{{"e1"}, {"c1"}, Piece{'K'}, MoveType::castling}));
                }

                SECTION("blocked")
                {
                    const Board board = Board::create_from_letter_data({
                        "rn--kn-r",
                        "--------",
                        "--------",
                        "--------",
                        "--------",
                        "--------",
                        "--------",
                        "R-N-K-NR",
                    });

                    CHECK(create_king_castling_moves(board, BoardPiece{Piece{'k'}, Square{"e8"}}, moves) == 0);
                    CHECK(create_king_castling_moves(board, BoardPiece{Piece{'K'}, Square{"e1"}}, moves) == 0);

                    CHECK(moves.size() == 0);
                }

                SECTION("king or rooks moved")
                {
                    const Board board = Board::create_from_letter_data({
                        "r--k---r",
                        "--------",
                        "--------",
                        "--------",
                        "--------",
                        "--------",
                        "-------R",
                        "-R--K---",
                    });

                    CHECK(create_king_castling_moves(board, BoardPiece{Piece{'k'}, Square{"d8"}}, moves) == 0);
                    CHECK(create_king_castling_moves(board, BoardPiece{Piece{'K'}, Square{"e1"}}, moves) == 0);

                    CHECK(moves.size() == 0);
                }
            }
        }

        SECTION("utility functions")
        {
            SECTION("nth_rank()")
            {
                CHECK(nth_rank(Player::black, 1) == 0);
                CHECK(nth_rank(Player::black, 2) == 1);
                CHECK(nth_rank(Player::black, 7) == 6);
                CHECK(nth_rank(Player::black, 8) == 7);

                CHECK(nth_rank(Player::white, 1) == 7);
                CHECK(nth_rank(Player::white, 2) == 6);
                CHECK(nth_rank(Player::white, 7) == 1);
                CHECK(nth_rank(Player::white, 8) == 0);
            }

            SECTION("on_second_rank()")
            {
                CHECK(on_second_rank(BoardPiece{Piece{Player::black, PieceType::pawn}, Square{"a7"}}));
                CHECK(on_second_rank(BoardPiece{Piece{Player::white, PieceType::pawn}, Square{"a2"}}));

                CHECK(on_second_rank(BoardPiece{Piece{Player::black, PieceType::pawn}, Square{"a8"}}) == false);
                CHECK(on_second_rank(BoardPiece{Piece{Player::black, PieceType::pawn}, Square{"a6"}}) == false);
                CHECK(on_second_rank(BoardPiece{Piece{Player::black, PieceType::pawn}, Square{"a2"}}) == false);
                CHECK(on_second_rank(BoardPiece{Piece{Player::black, PieceType::pawn}, Square{"a1"}}) == false);
                CHECK(on_second_rank(BoardPiece{Piece{Player::white, PieceType::pawn}, Square{"a1"}}) == false);
                CHECK(on_second_rank(BoardPiece{Piece{Player::white, PieceType::pawn}, Square{"a3"}}) == false);
                CHECK(on_second_rank(BoardPiece{Piece{Player::white, PieceType::pawn}, Square{"a7"}}) == false);
                CHECK(on_second_rank(BoardPiece{Piece{Player::white, PieceType::pawn}, Square{"a8"}}) == false);
            }

            SECTION("count_moves()")
            {
                Moves moves{
                    Move{Square{"a1"}, Square{"a2"}, Piece{'p'}, MoveType::normal},
                    Move{Square{"a1"}, Square{"a2"}, Piece{'p'}, MoveType::normal},
                    Move{Square{"a1"}, Square{"a2"}, Piece{'p'}, MoveType::normal},
                    Move{Square{"a1"}, Square{"a2"}, Piece{'p'}, MoveType::capture},
                    Move{Square{"a1"}, Square{"a2"}, Piece{'p'}, MoveType::capture},
                    Move{Square{"a1"}, Square{"a2"}, Piece{'p'}, MoveType::en_passant},
                    Move{Square{"a1"}, Square{"a2"}, Piece{'p'}, MoveType::promotion},
                    Move{Square{"a1"}, Square{"a2"}, Piece{'p'}, MoveType::castling},
                    Move{Square{"a1"}, Square{"a2"}, Piece{'p'}, MoveType::castling},
                };

                CHECK(count_moves(moves, MoveType::normal) == 3);
                CHECK(count_moves(moves, MoveType::capture) == 2);
                CHECK(count_moves(moves, MoveType::en_passant) == 1);
                CHECK(count_moves(moves, MoveType::promotion) == 1);
                CHECK(count_moves(moves, MoveType::castling) == 2);

                CHECK(count_moves({}, MoveType::normal) == 0);
            }

            SECTION("forward_move_offset()")
            {
                CHECK(forward_move_offset(Player::white) == MoveOffset{0, -1});
                CHECK(forward_move_offset(Player::black) == MoveOffset{0, 1});
            }

            SECTION("diagonal_move_offset()")
            {
                CHECK(diagonal_move_offset(MoveOffset{-1, 0}, MoveOffset{0, -1}) == MoveOffset{-1, -1});
                CHECK(diagonal_move_offset(MoveOffset{-1, 0}, MoveOffset{0, 1}) == MoveOffset{-1, 1});
                CHECK(diagonal_move_offset(MoveOffset{1, 0}, MoveOffset{0, -1}) == MoveOffset{1, -1});
                CHECK(diagonal_move_offset(MoveOffset{1, 0}, MoveOffset{0, 1}) == MoveOffset{1, 1});
            }
        }
    }
}

}  // namespace chess
