#include "catch2/catch_test_macros.hpp"

#include "../src/game/win_conditions.hpp"

namespace chess {

TEST_CASE("game/win_conditions")
{
    SECTION("an empty board is game over")
    {
        CHECK(game_over(get_win_condition(Board{}, GameState{})));
    }

    SECTION("a new board with default pieces is not game over")
    {
        CHECK(game_over(get_win_condition(Board::create_with_default_pieces(), GameState{})) == false);
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
        CHECK(game_over(WinCondition::stalemate));
        CHECK(game_over(WinCondition::fifty_move_rule));
    }

    SECTION("win: checkmate")
    {
        SECTION("example 1")
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
            CHECK(get_win_condition(board, GameState{}) == WinCondition::checkmate_white);
        }

        SECTION("example 2")
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
            CHECK(get_win_condition(board, GameState{}) == WinCondition::checkmate_white);
        }

        SECTION("example 3")
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
            CHECK(get_win_condition(board, GameState{}) == WinCondition::checkmate_white);
        }

        SECTION("example 4")
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
            CHECK(get_win_condition(board, GameState{}) == WinCondition::checkmate_black);
        }

        SECTION("example 5")
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
            CHECK(get_win_condition(board, GameState{}) == WinCondition::checkmate_black);
        }

        SECTION("example 6")
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
            CHECK(get_win_condition(board, GameState{}) == WinCondition::checkmate_black);
        }

        SECTION("example 7")
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
            CHECK(get_win_condition(board, GameState{}) == WinCondition::checkmate_black);
        }

        SECTION("example 8")
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
            CHECK(get_win_condition(board, GameState{}) == WinCondition::checkmate_black);
        }

        SECTION("example 9")
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
            CHECK(get_win_condition(board, GameState{}) == WinCondition::checkmate_black);
        }

        SECTION("example 10")
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
            CHECK(get_win_condition(board, GameState{}) == WinCondition::checkmate_black);
        }
    }

    SECTION("draw: stalemate")
    {
        SECTION("example 1")
        {
            Board board = Board::create_from_letter_data({
                "-------k",
                "--------",
                "------Q-",
                "--------",
                "--------",
                "--------",
                "--------",
                "K-------",
            });

            CHECK(is_stalemate(board, Player::black));
            CHECK(is_stalemate(board, Player::white) == false);
            CHECK(get_win_condition(board, GameState{}) == WinCondition::stalemate);
        }

        SECTION("example 2")
        {
            Board board = Board::create_from_letter_data({
                "-----k--",
                "-----P--",
                "-----K--",
                "--------",
                "--------",
                "--------",
                "--------",
                "--------",
            });

            CHECK(is_stalemate(board, Player::black));
            CHECK(is_stalemate(board, Player::white) == false);
            CHECK(get_win_condition(board, GameState{}) == WinCondition::stalemate);
        }

        SECTION("example 3")
        {
            Board board = Board::create_from_letter_data({
                "kb-----R",
                "--------",
                "-K------",
                "--------",
                "--------",
                "--------",
                "--------",
                "--------",
            });

            CHECK(is_stalemate(board, Player::black));
            CHECK(is_stalemate(board, Player::white) == false);
            CHECK(get_win_condition(board, GameState{}) == WinCondition::stalemate);
        }

        SECTION("example 4")
        {
            Board board = Board::create_from_letter_data({
                "--------",
                "--------",
                "--------",
                "------K-",
                "--------",
                "-Q------",
                "p-------",
                "k-------",
            });

            CHECK(is_stalemate(board, Player::black));
            CHECK(is_stalemate(board, Player::white) == false);
            CHECK(get_win_condition(board, GameState{}) == WinCondition::stalemate);
        }

        SECTION("example 5")
        {
            Board board = Board::create_from_letter_data({
                "k-------",
                "P-------",
                "K-------",
                "--------",
                "-----B--",
                "--------",
                "--------",
                "--------",
            });

            CHECK(is_stalemate(board, Player::black));
            CHECK(is_stalemate(board, Player::white) == false);
            CHECK(get_win_condition(board, GameState{}) == WinCondition::stalemate);
        }

        SECTION("example 6")
        {
            Board board = Board::create_from_letter_data({
                "--------",
                "------p-",
                "-----p--",
                "-----k-K",
                "-------P",
                "--------",
                "--------",
                "--------",
            });

            CHECK(is_stalemate(board, Player::white));
            CHECK(is_stalemate(board, Player::black) == false);
            CHECK(get_win_condition(board, GameState{}) == WinCondition::stalemate);
        }

        SECTION("example 7")
        {
            Board board = Board::create_from_letter_data({
                "--------",
                "-----KBk",
                "--------",
                "--------",
                "p-------",
                "P-------",
                "--------",
                "--------",
            });

            CHECK(is_stalemate(board, Player::black));
            CHECK(is_stalemate(board, Player::white) == false);
            CHECK(get_win_condition(board, GameState{}) == WinCondition::stalemate);
        }
    }

    SECTION("draw: fifty-move rule")
    {
        SECTION("fifty consecutive full moves without a capture or a pawn move")
        {
            CHECK(get_win_condition(Board::create_with_default_pieces(), GameState{}) != WinCondition::fifty_move_rule);
            CHECK(get_win_condition(Board::create_with_default_pieces(), GameState{49, 200, CastlingAbility{}, std::nullopt}) != WinCondition::fifty_move_rule);
            CHECK(get_win_condition(Board::create_with_default_pieces(), GameState{50, 200, CastlingAbility{}, std::nullopt}) == WinCondition::fifty_move_rule);
            CHECK(get_win_condition(Board::create_with_default_pieces(), GameState{51, 200, CastlingAbility{}, std::nullopt}) == WinCondition::fifty_move_rule);
        }

        SECTION("checkmate takes precedence over the fifty-move rule")
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

            CHECK(get_win_condition(board, GameState{50, 200, CastlingAbility{}, std::nullopt}) == WinCondition::checkmate_white);
        }
    }
}

}  // namespace chess
