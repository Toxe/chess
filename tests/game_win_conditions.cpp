#include "catch2/catch_test_macros.hpp"

#include "../src/game/win_conditions.hpp"

namespace chess {

TEST_CASE("game/win_conditions")
{
    SECTION("an empty board is game over")
    {
        CHECK(game_over(get_win_condition(Board{})));
    }

    SECTION("a new board with default pieces is not game over")
    {
        CHECK(game_over(get_win_condition(Board::create_with_default_pieces())) == false);
    }

    SECTION("a game without a win condition is not game over")
    {
        CHECK(game_over(WinCondition::none) == false);
    }

    SECTION("a checkmate means game over")
    {
        CHECK(game_over(WinCondition::checkmate_white));
        CHECK(game_over(WinCondition::checkmate_black));
    }

    SECTION("a draw means game over")
    {
        CHECK(game_over(WinCondition::draw));
    }

    SECTION("checkmate")
    {
        SECTION("checkmate white #1")
        {
            Board board = Board::create_from_letter_data({
                "----k---",
                "--------",
                "--------",
                "-------r",
                "--------",
                "--------",
                "-----PP-",
                "-----RKq",
            });

            CHECK(is_checkmate(board, Player::white));
            CHECK(is_checkmate(board, Player::black) == false);
        }

        SECTION("checkmate white #2")
        {
            Board board = Board::create_from_letter_data({
                "rnb-kbnr",
                "pppp-ppp",
                "--------",
                "----p---",
                "------Pq",
                "-----P--",
                "PPPPP--P",
                "RNBQKBNR",
            });

            CHECK(is_checkmate(board, Player::white));
            CHECK(is_checkmate(board, Player::black) == false);
        }

        SECTION("checkmate white #3")
        {
            Board board = Board::create_from_letter_data({
                "-Q------",
                "-----pk-",
                "--p---p-",
                "-p--N--p",
                "-b-----P",
                "-bn-----",
                "--r---P-",
                "--K-----",
            });

            CHECK(is_checkmate(board, Player::white));
            CHECK(is_checkmate(board, Player::black) == false);
        }

        SECTION("checkmate black #1")
        {
            Board board = Board::create_from_letter_data({
                "--------",
                "--------",
                "--------",
                "-----K-k",
                "--------",
                "--------",
                "--------",
                "-------R",
            });

            CHECK(is_checkmate(board, Player::black));
            CHECK(is_checkmate(board, Player::white) == false);
        }

        SECTION("checkmate black #2")
        {
            Board board = Board::create_from_letter_data({
                "--------",
                "--------",
                "kQK-----",
                "--------",
                "--------",
                "--------",
                "--------",
                "--------",
            });

            CHECK(is_checkmate(board, Player::black));
            CHECK(is_checkmate(board, Player::white) == false);
        }

        SECTION("checkmate black #3")
        {
            Board board = Board::create_from_letter_data({
                "--------",
                "--------",
                "-----K-k",
                "--------",
                "--------",
                "--------",
                "--------",
                "-------Q",
            });

            CHECK(is_checkmate(board, Player::black));
            CHECK(is_checkmate(board, Player::white) == false);
        }

        SECTION("checkmate black #4")
        {
            Board board = Board::create_from_letter_data({
                "--------",
                "--------",
                "--------",
                "--------",
                "--------",
                "------K-",
                "--------",
                "---Q---k",
            });

            CHECK(is_checkmate(board, Player::black));
            CHECK(is_checkmate(board, Player::white) == false);
        }

        SECTION("checkmate black #5")
        {
            Board board = Board::create_from_letter_data({
                "--------",
                "-------Q",
                "--------",
                "-------k",
                "-----K--",
                "--------",
                "--------",
                "--------",
            });

            CHECK(is_checkmate(board, Player::black));
            CHECK(is_checkmate(board, Player::white) == false);
        }

        SECTION("checkmate black #6")
        {
            Board board = Board::create_from_letter_data({
                "---k---R",
                "--------",
                "---K----",
                "--------",
                "--------",
                "--------",
                "--------",
                "--------",
            });

            CHECK(is_checkmate(board, Player::black));
            CHECK(is_checkmate(board, Player::white) == false);
        }

        SECTION("checkmate black #7")
        {
            Board board = Board::create_from_letter_data({
                "-k------",
                "-B------",
                "-K-B----",
                "--------",
                "--------",
                "--------",
                "--------",
                "--------",
            });

            CHECK(is_checkmate(board, Player::black));
            CHECK(is_checkmate(board, Player::white) == false);
        }
    }
}

}  // namespace chess
