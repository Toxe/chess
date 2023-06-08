#include <utility>
#include <vector>

#include "catch2/catch_test_macros.hpp"

#include "../src/app/app_controller.hpp"
#include "../src/board/board.hpp"
#include "../src/command/command_factory.hpp"
#include "../src/game/game_players.hpp"
#include "../src/input/eval_input.hpp"
#include "../src/move_generator/game_state.hpp"
#include "../src/output/console_writer.hpp"

namespace chess {

[[nodiscard]] bool check_legal_move_input(const Player player, Board& board, const GameState game_state, const std::string_view input, const Move expected_move)
{
    const auto move = eval_move_input(player, board, game_state, input);

    INFO("error: " << (move.has_value() ? "-" : move.error()));
    CHECK(move.has_value());

    if (!move)
        return false;

    return move == expected_move;
}

[[nodiscard]] bool check_illegal_move_input(const Player player, Board& board, const GameState game_state, const std::string_view input, const std::string_view error_msg)
{
    const auto move = eval_move_input(player, board, game_state, input);
    CHECK(move.has_value() == false);

    if (move.has_value())
        return false;

    CHECK(move.error() == error_msg);
    return move.error() == error_msg;
}

TEST_CASE("input/eval_input")
{
    Board board = Board::create_from_letter_data({
        "N-n-k--r",
        "rP-p----",
        "----pP--",
        "-B---Pp-",
        "-pP-----",
        "--------",
        "------p-",
        "R---KB-R",
    });
    GameState game_state{0, 1, CastlingAbility{CastlingRight::black_king, CastlingRight::white_king, CastlingRight::white_queen}, Square{"c3"}};
    GamePlayers game_players{PlayerType::human, PlayerType::human};
    AppController controller;
    ConsoleWriter console_writer{false};
    const CommandFactory command_factory{board, game_state, game_players, controller, console_writer};

    SECTION("eval_keyword_command()")
    {
        SECTION("invalid input returns an invalid command (nullopt)")
        {
            CHECK(eval_keyword_command(command_factory, "").has_value() == false);
            CHECK(eval_keyword_command(command_factory, "----").has_value() == false);
            CHECK(eval_keyword_command(command_factory, "e4wvrtgf").has_value() == false);
        }

        SECTION("simple keyword commands")
        {
            CHECK(eval_keyword_command(command_factory, "?").has_value());
            CHECK(eval_keyword_command(command_factory, "h").has_value());
            CHECK(eval_keyword_command(command_factory, "q").has_value());
            CHECK(eval_keyword_command(command_factory, "r").has_value());
            CHECK(eval_keyword_command(command_factory, "u").has_value());
            CHECK(eval_keyword_command(command_factory, "exit").has_value());
            CHECK(eval_keyword_command(command_factory, "help").has_value());
            CHECK(eval_keyword_command(command_factory, "quit").has_value());
            CHECK(eval_keyword_command(command_factory, "redo").has_value());
            CHECK(eval_keyword_command(command_factory, "undo").has_value());
        }
    }

    SECTION("eval_move_input()")
    {
        SECTION("accept legal moves")
        {
            SECTION("normal")
            {
                CHECK(check_legal_move_input(Player::white, board, game_state, "e1e2", Move::create_normal({"e1"}, {"e2"}, Piece{'K'})));
                CHECK(check_legal_move_input(Player::black, board, game_state, "a7a6", Move::create_normal({"a7"}, {"a6"}, Piece{'r'})));
            }

            SECTION("promotion")
            {
                CHECK(check_legal_move_input(Player::black, board, game_state, "g2g1q", Move::create_promotion({"g2"}, {"g1"}, Piece{'q'})));
                CHECK(check_legal_move_input(Player::white, board, game_state, "b7b8q", Move::create_promotion({"b7"}, {"b8"}, Piece{'Q'})));
            }

            SECTION("capture")
            {
                CHECK(check_legal_move_input(Player::white, board, game_state, "f1g2", Move::create_capture({"f1"}, {"g2"}, Piece{'B'}, Piece{'p'})));
                CHECK(check_legal_move_input(Player::black, board, game_state, "e6f5", Move::create_capture({"e6"}, {"f5"}, Piece{'p'}, Piece{'P'})));  // pawn
            }

            SECTION("capture and promotion")  // player input (the promoted piece) automatically converted to lowercase
            {
                CHECK(check_legal_move_input(Player::black, board, game_state, "g2h1n", Move::create_capture_and_promotion({"g2"}, {"h1"}, Piece{'n'}, Piece{'R'})));
                CHECK(check_legal_move_input(Player::white, board, game_state, "b7c8q", Move::create_capture_and_promotion({"b7"}, {"c8"}, Piece{'Q'}, Piece{'n'})));
            }

            SECTION("castling")
            {
                SECTION("with 0")
                {
                    CHECK(check_legal_move_input(Player::black, board, game_state, "0-0", Move::create_castling({"e8"}, {"g8"}, Piece{'k'})));
                    CHECK(check_legal_move_input(Player::white, board, game_state, "0-0-0", Move::create_castling({"e1"}, {"c1"}, Piece{'K'})));
                }

                SECTION("with O")  // player input automatically converted to lowercase
                {
                    CHECK(check_legal_move_input(Player::black, board, game_state, "o-o", Move::create_castling({"e8"}, {"g8"}, Piece{'k'})));
                    CHECK(check_legal_move_input(Player::white, board, game_state, "o-o-o", Move::create_castling({"e1"}, {"c1"}, Piece{'K'})));
                }
            }

            SECTION("en passant")
            {
                CHECK(check_legal_move_input(Player::black, board, game_state, "b4c3", Move::create_en_passant({"b4"}, {"c3"}, Piece{'p'})));
            }
        }

        SECTION("refuse invalid or illegal moves")
        {
            SECTION("no piece found")
            {
                CHECK(check_illegal_move_input(Player::black, board, game_state, "b8b7", "no piece found"));
                CHECK(check_illegal_move_input(Player::white, board, game_state, "a2b3", "no piece found"));
            }

            SECTION("can only move own pieces")
            {
                CHECK(check_illegal_move_input(Player::black, board, game_state, "e1e2", "can only move own pieces"));
                CHECK(check_illegal_move_input(Player::white, board, game_state, "a7b7", "can only move own pieces"));
                CHECK(check_illegal_move_input(Player::black, board, game_state, "f1g2", "can only move own pieces"));
                CHECK(check_illegal_move_input(Player::white, board, game_state, "g2g1q", "can only move own pieces"));
            }

            SECTION("cannot capture own pieces")
            {
                CHECK(check_illegal_move_input(Player::white, board, game_state, "e1f1", "cannot capture own pieces"));
                CHECK(check_illegal_move_input(Player::white, board, game_state, "c4b5", "cannot capture own pieces"));  // pawn
                CHECK(check_illegal_move_input(Player::white, board, game_state, "b7a8q", "cannot capture own pieces"));  // capture and promotion
            }

            SECTION("invalid promotion piece")
            {
                CHECK(check_illegal_move_input(Player::black, board, game_state, "g2g1p", "invalid promotion piece"));
                CHECK(check_illegal_move_input(Player::black, board, game_state, "g2g1k", "invalid promotion piece"));
            }

            SECTION("no castling right")
            {
                CHECK(check_illegal_move_input(Player::black, board, game_state, "0-0-0", "illegal move"));
            }

            SECTION("castling blocked")
            {
                CHECK(check_illegal_move_input(Player::white, board, game_state, "0-0", "illegal move"));
            }

            SECTION("en passant target square not set")
            {
                CHECK(check_illegal_move_input(Player::white, board, game_state, "f6e7", "illegal move"));
            }

            SECTION("en passant from illegal rank")
            {
                CHECK(check_illegal_move_input(Player::white, board, game_state, "f6e7", "illegal move"));
            }
        }

        SECTION("refuse ill-formed input")
        {
            SECTION("input too short")
            {
                CHECK(check_illegal_move_input(Player::white, board, game_state, "", "invalid input"));
                CHECK(check_illegal_move_input(Player::white, board, game_state, "?", "invalid input"));
                CHECK(check_illegal_move_input(Player::white, board, game_state, "a1", "invalid input"));
            }

            SECTION("input too long")
            {
                CHECK(check_illegal_move_input(Player::white, board, game_state, "??????", "invalid input"));
                CHECK(check_illegal_move_input(Player::white, board, game_state, "12345678", "invalid input"));
                CHECK(check_illegal_move_input(Player::white, board, game_state, "a1a2??", "invalid input"));
            }

            SECTION("invalid source or destination squares")
            {
                CHECK(check_illegal_move_input(Player::white, board, game_state, "x9a1", "invalid source square"));
                CHECK(check_illegal_move_input(Player::white, board, game_state, "a1y9", "invalid destination square"));
            }

            SECTION("castling ill-formatted")
            {
                CHECK(check_illegal_move_input(Player::white, board, game_state, "0", "invalid input"));
                CHECK(check_illegal_move_input(Player::white, board, game_state, "o", "invalid input"));
                CHECK(check_illegal_move_input(Player::white, board, game_state, "0-", "invalid input"));
                CHECK(check_illegal_move_input(Player::white, board, game_state, "o-", "invalid input"));
                CHECK(check_illegal_move_input(Player::white, board, game_state, "0-0-", "invalid input"));
                CHECK(check_illegal_move_input(Player::white, board, game_state, "o-o-", "invalid input"));
                CHECK(check_illegal_move_input(Player::white, board, game_state, "0-0-0-", "invalid input"));
                CHECK(check_illegal_move_input(Player::white, board, game_state, "o-o-o-", "invalid input"));
            }

            SECTION("invalid promotion piece")
            {
                CHECK(check_illegal_move_input(Player::black, board, game_state, "g2g1?", "invalid input"));
                CHECK(check_illegal_move_input(Player::black, board, game_state, "g2g13", "invalid input"));
                CHECK(check_illegal_move_input(Player::black, board, game_state, "g2g1-", "invalid input"));
            }
        }
    }
}

}  // namespace chess
