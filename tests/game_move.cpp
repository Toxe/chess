#include "catch2/catch_test_macros.hpp"

#include "../src/game/move.hpp"

namespace chess {

TEST_CASE("game/move")
{
    SECTION("construct")
    {
        SECTION("normal")
        {
            const auto move = Move::create_normal(Square{"d2"}, Square{"d4"}, Piece{'P'});

            CHECK(move.from == Square{"d2"});
            CHECK(move.to == Square{"d4"});
            CHECK(move.type == MoveType::normal);
            CHECK(move.piece == Piece{'P'});
            CHECK(move.captured_piece == no_piece);
        }

        SECTION("promotion")
        {
            const auto move_white = Move::create_promotion(Square{"g7"}, Square{"g8"}, Piece{'Q'});
            const auto move_black = Move::create_promotion(Square{"g2"}, Square{"g1"}, Piece{'q'});

            CHECK(move_white.from == Square{"g7"});
            CHECK(move_white.to == Square{"g8"});
            CHECK(move_white.type == MoveType::promotion);
            CHECK(move_white.piece == Piece{'Q'});
            CHECK(move_white.captured_piece == no_piece);

            CHECK(move_black.from == Square{"g2"});
            CHECK(move_black.to == Square{"g1"});
            CHECK(move_black.type == MoveType::promotion);
            CHECK(move_black.piece == Piece{'q'});
            CHECK(move_black.captured_piece == no_piece);
        }

        SECTION("capture")
        {
            const auto move = Move::create_capture(Square{"h1"}, Square{"h8"}, Piece{'R'}, Piece{'r'});

            CHECK(move.from == Square{"h1"});
            CHECK(move.to == Square{"h8"});
            CHECK(move.type == MoveType::capture);
            CHECK(move.piece == Piece{'R'});
            CHECK(move.captured_piece == Piece{'r'});
        }

        SECTION("capture_and_promotion")
        {
            const auto move_white = Move::create_capture_and_promotion(Square{"g7"}, Square{"h8"}, Piece{'Q'}, Piece{'r'});
            const auto move_black = Move::create_capture_and_promotion(Square{"g2"}, Square{"h1"}, Piece{'q'}, Piece{'R'});

            CHECK(move_white.from == Square{"g7"});
            CHECK(move_white.to == Square{"h8"});
            CHECK(move_white.type == MoveType::capture_and_promotion);
            CHECK(move_white.piece == Piece{'Q'});
            CHECK(move_white.captured_piece == Piece{'r'});

            CHECK(move_black.from == Square{"g2"});
            CHECK(move_black.to == Square{"h1"});
            CHECK(move_black.type == MoveType::capture_and_promotion);
            CHECK(move_black.piece == Piece{'q'});
            CHECK(move_black.captured_piece == Piece{'R'});
        }

        SECTION("castling")
        {
            SECTION("kingside")
            {
                const auto move_white = Move::create_castling(Square{"e1"}, Square{"g1"}, Piece{'K'});
                const auto move_black = Move::create_castling(Square{"e8"}, Square{"g8"}, Piece{'k'});

                CHECK(move_white.from == Square{"e1"});
                CHECK(move_white.to == Square{"g1"});
                CHECK(move_white.type == MoveType::castling);
                CHECK(move_white.piece == Piece{'K'});
                CHECK(move_white.captured_piece == no_piece);

                CHECK(move_black.from == Square{"e8"});
                CHECK(move_black.to == Square{"g8"});
                CHECK(move_black.type == MoveType::castling);
                CHECK(move_black.piece == Piece{'k'});
                CHECK(move_black.captured_piece == no_piece);
            }

            SECTION("queenside")
            {
                const auto move_white = Move::create_castling(Square{"e1"}, Square{"c1"}, Piece{'K'});
                const auto move_black = Move::create_castling(Square{"e8"}, Square{"c8"}, Piece{'k'});

                CHECK(move_white.from == Square{"e1"});
                CHECK(move_white.to == Square{"c1"});
                CHECK(move_white.type == MoveType::castling);
                CHECK(move_white.piece == Piece{'K'});
                CHECK(move_white.captured_piece == no_piece);

                CHECK(move_black.from == Square{"e8"});
                CHECK(move_black.to == Square{"c8"});
                CHECK(move_black.type == MoveType::castling);
                CHECK(move_black.piece == Piece{'k'});
                CHECK(move_black.captured_piece == no_piece);
            }
        }

        SECTION("en_passant")
        {
            SECTION("from left side")
            {
                const auto move_white = Move::create_en_passant(Square{"d5"}, Square{"e6"}, Piece{'P'});
                const auto move_black = Move::create_en_passant(Square{"a4"}, Square{"b3"}, Piece{'p'});

                CHECK(move_white.from == Square{"d5"});
                CHECK(move_white.to == Square{"e6"});
                CHECK(move_white.type == MoveType::en_passant);
                CHECK(move_white.piece == Piece{'P'});
                CHECK(move_white.captured_piece == Piece{'p'});

                CHECK(move_black.from == Square{"a4"});
                CHECK(move_black.to == Square{"b3"});
                CHECK(move_black.type == MoveType::en_passant);
                CHECK(move_black.piece == Piece{'p'});
                CHECK(move_black.captured_piece == Piece{'P'});
            }

            SECTION("from right side")
            {
                const auto move_white = Move::create_en_passant(Square{"f5"}, Square{"e6"}, Piece{'P'});
                const auto move_black = Move::create_en_passant(Square{"c4"}, Square{"b3"}, Piece{'p'});

                CHECK(move_white.from == Square{"f5"});
                CHECK(move_white.to == Square{"e6"});
                CHECK(move_white.type == MoveType::en_passant);
                CHECK(move_white.piece == Piece{'P'});
                CHECK(move_white.captured_piece == Piece{'p'});

                CHECK(move_black.from == Square{"c4"});
                CHECK(move_black.to == Square{"b3"});
                CHECK(move_black.type == MoveType::en_passant);
                CHECK(move_black.piece == Piece{'p'});
                CHECK(move_black.captured_piece == Piece{'P'});
            }
        }
    }

    SECTION("comparison")
    {
        const auto move = Move::create_normal(Square{"d2"}, Square{"d4"}, Piece{'P'});

        CHECK(move == move);
        CHECK(move != Move::create_capture(Square{"d2"}, Square{"d4"}, Piece{'P'}, Piece{'p'}));
        CHECK(move != Move::create_castling(Square{"e8"}, Square{"c8"}, Piece{'k'}));
        CHECK(move != Move::create_normal(Square{"d2"}, Square{"d4"}, Piece{'N'}));
        CHECK(move != Move::create_normal(Square{"d2"}, Square{"d3"}, Piece{'P'}));
        CHECK(move != Move::create_normal(Square{"d3"}, Square{"d4"}, Piece{'P'}));

        CHECK((move != move) == false);
        CHECK((move == Move::create_capture(Square{"d2"}, Square{"d4"}, Piece{'P'}, Piece{'p'})) == false);
        CHECK((move == Move::create_castling(Square{"e8"}, Square{"c8"}, Piece{'k'})) == false);
        CHECK((move == Move::create_normal(Square{"d2"}, Square{"d4"}, Piece{'N'})) == false);
        CHECK((move == Move::create_normal(Square{"d2"}, Square{"d3"}, Piece{'P'})) == false);
        CHECK((move == Move::create_normal(Square{"d3"}, Square{"d4"}, Piece{'P'})) == false);
    }

    SECTION("make_move() and undo_move() apply and revert moves")
    {
        auto board = Board::create_from_letter_data({
            "r---k--r",
            "------P-",
            "--------",
            "---PpP--",
            "pPp-----",
            "--------",
            "---P----",
            "R---K--R",
        });
        const auto board_backup = board;

        SECTION("normal moves")
        {
            const auto move = Move::create_normal(Square{"d2"}, Square{"d4"}, Piece{'P'});

            make_move(board, move);
            CHECK(board.piece(move.from) == no_piece);
            CHECK(board.piece(move.to) == move.piece);

            undo_move(board, move);
            CHECK(board.piece(move.from) == move.piece);
            CHECK(board.piece(move.to) == no_piece);

            CHECK(board == board_backup);
        }

        SECTION("promotion")
        {
            const auto move = Move::create_promotion(Square{"g7"}, Square{"g8"}, Piece{'Q'});

            make_move(board, move);
            CHECK(board.piece(move.from) == no_piece);
            CHECK(board.piece(move.to) == move.piece);

            undo_move(board, move);
            CHECK(board.piece(move.from) == Piece{'P'});
            CHECK(board.piece(move.to) == no_piece);

            CHECK(board == board_backup);
        }

        SECTION("capture")
        {
            const auto move = Move::create_capture(Square{"h1"}, Square{"h8"}, Piece{'R'}, Piece{'r'});

            make_move(board, move);
            CHECK(board.piece(move.from) == no_piece);
            CHECK(board.piece(move.to) == move.piece);

            undo_move(board, move);
            CHECK(board.piece(move.from) == move.piece);
            CHECK(board.piece(move.to) == Piece{'r'});

            CHECK(board == board_backup);
        }

        SECTION("capture_and_promotion")
        {
            const auto move = Move::create_capture_and_promotion(Square{"g7"}, Square{"h8"}, Piece{'Q'}, Piece{'r'});

            make_move(board, move);
            CHECK(board.piece(move.from) == no_piece);
            CHECK(board.piece(move.to) == move.piece);

            undo_move(board, move);
            CHECK(board.piece(move.from) == Piece{'P'});
            CHECK(board.piece(move.to) == Piece{'r'});

            CHECK(board == board_backup);
        }

        SECTION("castling")
        {
            SECTION("white")
            {
                SECTION("kingside")
                {
                    const auto move = Move::create_castling(Square{"e1"}, Square{"g1"}, Piece{'K'});

                    make_move(board, move);
                    CHECK(board.piece(move.from) == no_piece);
                    CHECK(board.piece(move.to) == move.piece);
                    CHECK(board.piece(Square{"f1"}) == Piece{'R'});
                    CHECK(board.piece(Square{"h1"}) == no_piece);

                    undo_move(board, move);
                    CHECK(board.piece(move.from) == move.piece);
                    CHECK(board.piece(move.to) == no_piece);
                    CHECK(board.piece(Square{"f1"}) == no_piece);
                    CHECK(board.piece(Square{"h1"}) == Piece{'R'});

                    CHECK(board == board_backup);
                }

                SECTION("queenside")
                {
                    const auto move = Move::create_castling(Square{"e1"}, Square{"c1"}, Piece{'K'});

                    make_move(board, move);
                    CHECK(board.piece(move.from) == no_piece);
                    CHECK(board.piece(move.to) == move.piece);
                    CHECK(board.piece(Square{"d1"}) == Piece{'R'});
                    CHECK(board.piece(Square{"a1"}) == no_piece);

                    undo_move(board, move);
                    CHECK(board.piece(move.from) == move.piece);
                    CHECK(board.piece(move.to) == no_piece);
                    CHECK(board.piece(Square{"d1"}) == no_piece);
                    CHECK(board.piece(Square{"a1"}) == Piece{'R'});

                    CHECK(board == board_backup);
                }
            }

            SECTION("black")
            {
                SECTION("kingside")
                {
                    const auto move = Move::create_castling(Square{"e8"}, Square{"g8"}, Piece{'k'});

                    make_move(board, move);
                    CHECK(board.piece(move.from) == no_piece);
                    CHECK(board.piece(move.to) == move.piece);
                    CHECK(board.piece(Square{"f8"}) == Piece{'r'});
                    CHECK(board.piece(Square{"h8"}) == no_piece);

                    undo_move(board, move);
                    CHECK(board.piece(move.from) == move.piece);
                    CHECK(board.piece(move.to) == no_piece);
                    CHECK(board.piece(Square{"f8"}) == no_piece);
                    CHECK(board.piece(Square{"h8"}) == Piece{'r'});

                    CHECK(board == board_backup);
                }

                SECTION("queenside")
                {
                    const auto move = Move::create_castling(Square{"e8"}, Square{"c8"}, Piece{'k'});

                    make_move(board, move);
                    CHECK(board.piece(move.from) == no_piece);
                    CHECK(board.piece(move.to) == move.piece);
                    CHECK(board.piece(Square{"d8"}) == Piece{'r'});
                    CHECK(board.piece(Square{"a8"}) == no_piece);

                    undo_move(board, move);
                    CHECK(board.piece(move.from) == move.piece);
                    CHECK(board.piece(move.to) == no_piece);
                    CHECK(board.piece(Square{"d8"}) == no_piece);
                    CHECK(board.piece(Square{"a8"}) == Piece{'r'});

                    CHECK(board == board_backup);
                }
            }
        }

        SECTION("en_passant")
        {
            SECTION("white")
            {
                SECTION("from left side")
                {
                    const auto move = Move::create_en_passant(Square{"d5"}, Square{"e6"}, Piece{'P'});

                    make_move(board, move);
                    CHECK(board.piece(move.from) == no_piece);
                    CHECK(board.piece(move.to) == move.piece);
                    CHECK(board.piece(Square{"e5"}) == no_piece);

                    undo_move(board, move);
                    CHECK(board.piece(move.from) == move.piece);
                    CHECK(board.piece(move.to) == no_piece);
                    CHECK(board.piece(Square{"e5"}) == Piece{'p'});

                    CHECK(board == board_backup);
                }

                SECTION("from right side")
                {
                    const auto move = Move::create_en_passant(Square{"f5"}, Square{"e6"}, Piece{'P'});

                    make_move(board, move);
                    CHECK(board.piece(move.from) == no_piece);
                    CHECK(board.piece(move.to) == move.piece);
                    CHECK(board.piece(Square{"e5"}) == no_piece);

                    undo_move(board, move);
                    CHECK(board.piece(move.from) == move.piece);
                    CHECK(board.piece(move.to) == no_piece);
                    CHECK(board.piece(Square{"e5"}) == Piece{'p'});

                    CHECK(board == board_backup);
                }
            }

            SECTION("black")
            {
                SECTION("from left side")
                {
                    const auto move = Move::create_en_passant(Square{"a4"}, Square{"b3"}, Piece{'p'});

                    make_move(board, move);
                    CHECK(board.piece(move.from) == no_piece);
                    CHECK(board.piece(move.to) == move.piece);
                    CHECK(board.piece(Square{"b4"}) == no_piece);

                    undo_move(board, move);
                    CHECK(board.piece(move.from) == move.piece);
                    CHECK(board.piece(move.to) == no_piece);
                    CHECK(board.piece(Square{"b4"}) == Piece{'P'});

                    CHECK(board == board_backup);
                }

                SECTION("from right side")
                {
                    const auto move = Move::create_en_passant(Square{"c4"}, Square{"b3"}, Piece{'p'});

                    make_move(board, move);
                    CHECK(board.piece(move.from) == no_piece);
                    CHECK(board.piece(move.to) == move.piece);
                    CHECK(board.piece(Square{"b4"}) == no_piece);

                    undo_move(board, move);
                    CHECK(board.piece(move.from) == move.piece);
                    CHECK(board.piece(move.to) == no_piece);
                    CHECK(board.piece(Square{"b4"}) == Piece{'P'});

                    CHECK(board == board_backup);
                }
            }
        }
    }

    SECTION("check if a castling move is kingside or queenside")
    {
        SECTION("white")
        {
            CHECK(castling_kingside(Move::create_castling(Square{"e1"}, Square{"g1"}, Piece{'K'}).to));
            CHECK(castling_kingside(Move::create_castling(Square{"e1"}, Square{"c1"}, Piece{'K'}).to) == false);
            CHECK(castling_queenside(Move::create_castling(Square{"e1"}, Square{"g1"}, Piece{'K'}).to) == false);
            CHECK(castling_queenside(Move::create_castling(Square{"e1"}, Square{"c1"}, Piece{'K'}).to));
        }

        SECTION("black")
        {
            CHECK(castling_kingside(Move::create_castling(Square{"e8"}, Square{"g8"}, Piece{'k'}).to));
            CHECK(castling_kingside(Move::create_castling(Square{"e8"}, Square{"c8"}, Piece{'k'}).to) == false);
            CHECK(castling_queenside(Move::create_castling(Square{"e8"}, Square{"g8"}, Piece{'k'}).to) == false);
            CHECK(castling_queenside(Move::create_castling(Square{"e8"}, Square{"c8"}, Piece{'k'}).to));
        }
    }
}

}  // namespace chess
